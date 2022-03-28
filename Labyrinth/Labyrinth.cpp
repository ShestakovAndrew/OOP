#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <vector>
#include <stack>
#include <windows.h>
#include <string>

namespace
{
	const int8_t MAX_LABYRINTH_SIZE = 100;
	const int8_t VON_NEUMANN_AREA = 4;
	const int8_t MUR_AREA = 8;
	
	using Labyrinth = std::vector<std::vector<int16_t>>;

	struct PositionCell
	{
		int16_t row;
		int16_t col;
	};

	struct LabyrinthOffset
	{
		size_t lengthTop;
		size_t lengthLeft;
	};

	struct LabyrinthSize
	{
		size_t height;
		size_t width;
	};

	struct BordersLabyrinth
	{
		PositionCell top;
		PositionCell left;
		PositionCell right;
		PositionCell bottom;
	};

	struct LabyrintInfo
	{
		BordersLabyrinth bordersLabyrinth;
		LabyrinthOffset labyrinthOffset;
		LabyrinthSize labyrinthSize;
	};

	enum class LabyrinthCells
	{
		PATH = -4,
		END = -3,
		BLANK = -2,
		WALL = -1,
		START = 0,
	};

	std::unordered_map<char, LabyrinthCells> const LabyrinthCellsTable = {
			{' ', LabyrinthCells::BLANK},
			{'#', LabyrinthCells::WALL},
			{'A', LabyrinthCells::START},
			{'B', LabyrinthCells::END},
			{'-', LabyrinthCells::PATH},
	};

	std::unordered_map<LabyrinthCells, char> const InvertLabyrinthCellsTable = {
			{LabyrinthCells::BLANK, ' '},
			{LabyrinthCells::WALL, '#'},
			{LabyrinthCells::START, 'A'},
			{LabyrinthCells::END, 'B'},
			{LabyrinthCells::PATH, '-'},
	};
}

LabyrinthCells ToLabyrinthCellsEnum(int16_t labyrinthCell)
{
	return static_cast<LabyrinthCells>(labyrinthCell);
}

int16_t ToInt(LabyrinthCells labyrinthCell)
{
	return static_cast<int8_t>(labyrinthCell);
}

std::ifstream GetInputFileStream(std::string const& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open file for reading.");
	}
	return move(file);
}

void ArgumentsCountCheck(int argc)
{
	if (argc != 3)
	{
		std::cout << "Usage: labyrinth.exe <input file> <output file>" << std::endl
			<< "\t<input file> - path to input file." << std::endl
			<< "\t<output file> - path to output file." << std::endl;

		throw std::invalid_argument("Invalid arguments count.");
	}
}

void UpdateBorders(BordersLabyrinth& bordersLabyrinth, PositionCell const& cellPosition)
{
	if (bordersLabyrinth.left.col > cellPosition.col)
	{
		bordersLabyrinth.left = cellPosition;
	}

	if (bordersLabyrinth.bottom.row < cellPosition.row)
	{
		bordersLabyrinth.bottom = cellPosition;
	}

	if (bordersLabyrinth.right.col < cellPosition.col)
	{
		bordersLabyrinth.right = cellPosition;
	}
}

BordersLabyrinth GetBordersOfLabyrinthFromFile(std::string const& filePath)
{
	std::ifstream file = GetInputFileStream(filePath);

	BordersLabyrinth borders{};

	std::string fileLine;
	bool isFirstWall = true;
	int16_t row = 0;

	while (std::getline(file, fileLine))
	{
		int16_t col = 0;
		for (char const& labyrinthCell : fileLine)
		{
			if (LabyrinthCellsTable.find(labyrinthCell)->second == LabyrinthCells::WALL)
			{
				if (isFirstWall)
				{
					borders.top = { row, col };
					borders.left = { row, col };
					borders.right = { row, col };
					borders.bottom = { row, col };

					isFirstWall = false;
				}
				else
				{
					UpdateBorders(borders, { row, col });
				}
			}
			col++;
		}
		row++;
	}
	file.close();

	return borders;
}

LabyrintInfo GetLabyrinthInfoFromFile(std::string const& filePath)
{
	LabyrintInfo labyrinthInfo;
	
	labyrinthInfo.bordersLabyrinth = GetBordersOfLabyrinthFromFile(filePath);

	labyrinthInfo.labyrinthSize.height = (labyrinthInfo.bordersLabyrinth.bottom.row - labyrinthInfo.bordersLabyrinth.top.row) + 1;
	labyrinthInfo.labyrinthSize.width = (labyrinthInfo.bordersLabyrinth.right.col - labyrinthInfo.bordersLabyrinth.left.col) + 1;

	if ((labyrinthInfo.labyrinthSize.height > MAX_LABYRINTH_SIZE) or (labyrinthInfo.labyrinthSize.width > MAX_LABYRINTH_SIZE))
	{
		throw std::out_of_range("The readable labyrinth is too large. Use labyrinth size 100x100.");
	}

	labyrinthInfo.labyrinthOffset.lengthTop = labyrinthInfo.bordersLabyrinth.top.row;
	labyrinthInfo.labyrinthOffset.lengthLeft = labyrinthInfo.bordersLabyrinth.left.col;

	return labyrinthInfo;
}

Labyrinth GetLabyrinthFromArgv(int argc, char* argv[])
{
	ArgumentsCountCheck(argc);

	LabyrintInfo labyrinthInfo = GetLabyrinthInfoFromFile(argv[1]);

	std::ifstream file = GetInputFileStream(argv[1]);
	
	Labyrinth labyrinth;

	std::string fileLine;
	size_t fileRow = 0;

	while (std::getline(file, fileLine))
	{
		if (fileRow < labyrinthInfo.labyrinthOffset.lengthTop)
		{
			fileRow++;
			continue;
		}

		if ((fileRow - labyrinthInfo.labyrinthOffset.lengthTop) == labyrinthInfo.labyrinthSize.height) break;

		std::vector<int16_t> temp(labyrinthInfo.labyrinthSize.width, ToInt(LabyrinthCells::BLANK));
		size_t fileCol = 0;

		for (char const& labyrinthCell : fileLine)
		{
			if (fileCol < labyrinthInfo.labyrinthOffset.lengthLeft)
			{
				fileCol++;
				continue;
			}

			temp[fileCol++ - labyrinthInfo.labyrinthOffset.lengthLeft] = ToInt(LabyrinthCellsTable.find(labyrinthCell)->second);

		}

		labyrinth.push_back(temp);
		fileRow++;
	}
	file.close();

	return labyrinth;
}

PositionCell GetPositionFromLabyrinthOf(LabyrinthCells labyrinthCells, Labyrinth const& labyrinth)
{
	for (int16_t i = 0; i < labyrinth.size(); i++)
	{
		for (int16_t j = 0; j < labyrinth[i].size(); j++)
		{
			if (labyrinth[i][j] == ToInt(labyrinthCells)) return { i, j };
		}
	}

	throw std::invalid_argument("Cell not found.");
}

void ValidateLabyrinth(Labyrinth const& labyrinth)
{

}

bool CheckAllPosition(
	PositionCell currentÑell,
	int16_t sizeOfWave,
	Labyrinth& labyrinth,
	std::vector<PositionCell> offcetCell
)
{
	bool allMarked = true;

	for (size_t vicinity = 0; vicinity < MUR_AREA; ++vicinity)
	{
		size_t iy = currentÑell.row + offcetCell[vicinity].row;
		size_t ix = currentÑell.col + offcetCell[vicinity].col;

		if (iy >= 0 and iy < labyrinth.size() and
			ix >= 0 and ix < labyrinth[0].size() and
			(labyrinth[iy][ix] == ToInt(LabyrinthCells::BLANK) or
				labyrinth[iy][ix] == ToInt(LabyrinthCells::END)))
		{
			allMarked = false;
			labyrinth[iy][ix] = sizeOfWave + 1;
		}
	}
	return allMarked ? false : true;
}

bool CheackVonNeumannPositions(
	PositionCell currentÑell,
	int16_t sizeOfWave,
	Labyrinth& labyrinth
)
{
	std::vector<PositionCell> offcetCellVonNeumann = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0} 
	};

	return CheckAllPosition(currentÑell, sizeOfWave, labyrinth, offcetCellVonNeumann);
}

bool CheackMurPositions(
	PositionCell currentÑell,
	int16_t sizeOfWave,
	Labyrinth& labyrinth
)
{
	std::vector<PositionCell> offcetCellMur = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0},
		{-1, -1},
		{-1, 1},
		{1, -1},
		{1, 1}
	};

	return CheckAllPosition(currentÑell, sizeOfWave, labyrinth, offcetCellMur);
}

bool SpreadWaveInLabyrinth(
	Labyrinth& labyrinth,
	PositionCell start,
	PositionCell end
)
{
	labyrinth[start.row][start.col] = 0;
	int16_t wave = 0;
	bool allMarked;

	do
	{
		allMarked = true;
		for (int16_t labyrinthRow = 0; labyrinthRow < labyrinth.size(); ++labyrinthRow)
		{
			for (int16_t labyrinthCol = 0; labyrinthCol < labyrinth[labyrinthRow].size(); ++labyrinthCol)
			{
				if (labyrinth[labyrinthRow][labyrinthCol] == wave)
				{
					if (CheackMurPositions({ labyrinthRow, labyrinthCol }, wave, labyrinth)) allMarked = false;
				}
			}
		}
		wave++;
	} while (!allMarked and labyrinth[end.row][end.col] == ToInt(LabyrinthCells::END));

	return (labyrinth[end.row][end.col] == ToInt(LabyrinthCells::END)) ? false : true;
}

std::stack<PositionCell> GetShortestPathFromLabyrinth(
	Labyrinth& labyrinthWithWaves, 
	PositionCell startPosition, 
	PositionCell endPosition
)
{
	std::stack<PositionCell> path;

	std::vector<PositionCell> offcetCellMur = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0},
		{-1, -1},
		{-1, 1},
		{1, -1},
		{1, 1}
	};

	size_t waveLength = labyrinthWithWaves[endPosition.row][endPosition.col];
	int16_t x = endPosition.col;
	int16_t y = endPosition.row;

	while ((waveLength--) > 0)
	{
		for (size_t vicinity = 0; vicinity < MUR_AREA; ++vicinity)
		{
			size_t iy = y + offcetCellMur[vicinity].row;
			size_t ix = x + offcetCellMur[vicinity].col;

			if (iy >= 0 && iy < labyrinthWithWaves.size() &&
				ix >= 0 && ix < labyrinthWithWaves[0].size() &&
				labyrinthWithWaves[iy][ix] == waveLength)
			{
				y += offcetCellMur[vicinity].row;
				x += offcetCellMur[vicinity].col;
				break;
			}
		}
		path.push({ y,x });
	}
	return path;
}

Labyrinth SetShortestPathToLabyrinth(Labyrinth const& labyrinthWithoutPath, std::stack<PositionCell>& shortestPath)
{
	Labyrinth labyrinthWithPath = labyrinthWithoutPath;

	shortestPath.pop();
	while (!shortestPath.empty())
	{
		PositionCell positionCell = shortestPath.top();
		labyrinthWithPath[positionCell.row][positionCell.col] = ToInt(LabyrinthCells::PATH);
		shortestPath.pop();
	}
	return labyrinthWithPath;
}

Labyrinth GetLabyrinthWithShortestPathByPositions(
	PositionCell startPosition,
	PositionCell endPosition,
	Labyrinth& labyrinthWithoutShortestPath
)
{
	Labyrinth labyrinth = labyrinthWithoutShortestPath;

	if (!SpreadWaveInLabyrinth(labyrinth, startPosition, endPosition))
	{
		return labyrinthWithoutShortestPath;
	}

	std::stack<PositionCell> shortestPath = GetShortestPathFromLabyrinth(labyrinth, startPosition, endPosition);

	return SetShortestPathToLabyrinth(labyrinthWithoutShortestPath, shortestPath);
}

Labyrinth FindingShortestPathInLabyrinth(Labyrinth& labyrinth)
{
	ValidateLabyrinth(labyrinth);

	PositionCell start = GetPositionFromLabyrinthOf(LabyrinthCells::START, labyrinth);
	PositionCell end = GetPositionFromLabyrinthOf(LabyrinthCells::END, labyrinth);

	return GetLabyrinthWithShortestPathByPositions(start, end, labyrinth);
}

std::ofstream GetOutputFileStream(std::string const& filePath)
{
	std::ofstream file(filePath);
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open file for reading.");
	}
	return move(file);
}

void WriteLabyrinthInFile(std::string const& filePath, Labyrinth& labyrinth)
{
	std::ofstream file = GetOutputFileStream(filePath);

	for (auto& vectorOfCell : labyrinth)
	{
		for (auto& labyrinthCell : vectorOfCell)
		{
			file << InvertLabyrinthCellsTable.find(ToLabyrinthCellsEnum(labyrinthCell))->second;
		}
		file << std::endl;
	}
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	try
	{
		Labyrinth labyrinth = GetLabyrinthFromArgv(argc, argv);
		Labyrinth labyrinthWithShortestPath = FindingShortestPathInLabyrinth(labyrinth);
		WriteLabyrinthInFile(argv[2], labyrinthWithShortestPath);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}