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

#include "boost/algorithm/cxx11/one_of.hpp"

namespace
{
	const size_t MAX_LABYRINTH_SIZE = 100;

	struct PositionCell
	{
		int16_t row;
		int16_t colum;
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

	static std::vector<PositionCell> const OFFCET_CELL_MUR = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0},
		{-1, -1},
		{-1, 1},
		{1, -1},
		{1, 1}
	};
	static std::vector<PositionCell> const OFFCET_CELL_VON_NEUMANN = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0}
	};

	using Labyrinth = std::vector<std::vector<int16_t>>;
	using CheckFunction = std::function<bool(PositionCell const& positionCell, int16_t sizeOfWave, Labyrinth& labyrinth)>;

	enum class LabyrinthCells
	{
		PATH = -4,
		END,
		BLANK,
		WALL,
		START
	};
	enum class SearchSettings
	{
		VON_NEUMANN = 0,
		MUR
	};

	static std::unordered_map<char, LabyrinthCells> const LabyrinthCellsTable = {
			{' ', LabyrinthCells::BLANK},
			{'#', LabyrinthCells::WALL},
			{'A', LabyrinthCells::START},
			{'B', LabyrinthCells::END},
			{'.', LabyrinthCells::PATH},
	};
	static std::unordered_map<LabyrinthCells, char> const InvertLabyrinthCellsTable = {
			{LabyrinthCells::BLANK, ' '},
			{LabyrinthCells::WALL, '#'},
			{LabyrinthCells::START, 'A'},
			{LabyrinthCells::END, 'B'},
			{LabyrinthCells::PATH, '.'},
	};
	static std::unordered_map<std::string, SearchSettings> const SearchSettingsTable = {
			{"mur", SearchSettings::MUR},
			{"von-neumann", SearchSettings::VON_NEUMANN},
	};
}

LabyrinthCells ToLabyrinthCells(int16_t labyrinthCell)
{
	return static_cast<LabyrinthCells>(labyrinthCell);
}

int16_t ToInt(LabyrinthCells labyrinthCell)
{
	return static_cast<int8_t>(labyrinthCell);
}

void UpdateBorders(BordersLabyrinth& bordersLabyrinth, PositionCell const& cellPosition)
{
	if (bordersLabyrinth.left.colum > cellPosition.colum)
	{
		bordersLabyrinth.left = cellPosition;
	}

	if (bordersLabyrinth.bottom.row < cellPosition.row)
	{
		bordersLabyrinth.bottom = cellPosition;
	}

	if (bordersLabyrinth.right.colum < cellPosition.colum)
	{
		bordersLabyrinth.right = cellPosition;
	}
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

bool IsStartPosition(int16_t cell)
{
	return cell == ToInt(LabyrinthCells::START);
}

bool IsEndPosition(int16_t cell)
{
	return cell == ToInt(LabyrinthCells::END);
}

void ValidateLabyrinth(Labyrinth const& labyrinth)
{
	std::vector<int16_t> tempVector;
	for (auto& vectCell : labyrinth) tempVector.insert(tempVector.end(), vectCell.begin(), vectCell.end());

	if (!boost::algorithm::one_of(tempVector.begin(), tempVector.end(), IsEndPosition) or
		!boost::algorithm::one_of(tempVector.begin(), tempVector.end(), IsStartPosition))
	{
		throw std::out_of_range("The starting/end point is incorrect.");
	}
}

bool CheckPosition(PositionCell const& current—ell, int16_t sizeOfWave, Labyrinth& labyrinth, std::vector<PositionCell> const& offcetCell)
{
	bool allMarked = true;

	for (size_t vicinity = 0; vicinity < offcetCell.size(); ++vicinity)
	{
		size_t iy = current—ell.row + offcetCell[vicinity].row;
		size_t ix = current—ell.colum + offcetCell[vicinity].colum;

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

bool SpreadWaveInLabyrinth(Labyrinth& labyrinth, PositionCell start, PositionCell end, std::vector<PositionCell> const& offcetCell)
{
	labyrinth[start.row][start.colum] = 0;
	int16_t wave = 0;
	bool allMarked = false;

	do
	{
		allMarked = true;
		for (int16_t labyrinthRow = 0; labyrinthRow < labyrinth.size(); ++labyrinthRow)
		{
			for (int16_t labyrinthCol = 0; labyrinthCol < labyrinth[labyrinthRow].size(); ++labyrinthCol)
			{
				if (labyrinth[labyrinthRow][labyrinthCol] == wave)
				{
					if (CheckPosition({ labyrinthRow , labyrinthCol }, wave, labyrinth, offcetCell)) allMarked = false;
				}
			}
		}
		wave++;
	} while (!allMarked and labyrinth[end.row][end.colum] == ToInt(LabyrinthCells::END));

	return (labyrinth[end.row][end.colum] == ToInt(LabyrinthCells::END)) ? false : true;
}

Labyrinth SetShortestPathToLabyrinth(Labyrinth const& labyrinthWithoutPath, std::stack<PositionCell>& shortestPath)
{
	Labyrinth labyrinthWithPath = labyrinthWithoutPath;

	shortestPath.pop();
	while (!shortestPath.empty())
	{
		PositionCell positionCell = shortestPath.top();
		labyrinthWithPath[positionCell.row][positionCell.colum] = ToInt(LabyrinthCells::PATH);
		shortestPath.pop();
	}
	return labyrinthWithPath;
}

std::stack<PositionCell> GetFromLabyrinthShortestPath(
	Labyrinth& labyrinthWithWaves, 
	PositionCell const& startPosition, 
	PositionCell const& endPosition, 
	std::vector<PositionCell> const& offcetCell
)
{
	std::stack<PositionCell> path;

	size_t waveLength = labyrinthWithWaves[endPosition.row][endPosition.colum];
	int16_t x = endPosition.colum;
	int16_t y = endPosition.row;

	while ((waveLength--) > 0)
	{
		for (size_t vicinity = 0; vicinity < offcetCell.size(); ++vicinity)
		{
			size_t iy = y + offcetCell[vicinity].row;
			size_t ix = x + offcetCell[vicinity].colum;

			if (iy >= 0 && iy < labyrinthWithWaves.size() &&
				ix >= 0 && ix < labyrinthWithWaves[0].size() &&
				labyrinthWithWaves[iy][ix] == waveLength)
			{
				y += offcetCell[vicinity].row;
				x += offcetCell[vicinity].colum;
				break;
			}
		}
		path.push({ y,x });
	}
	return path;
}

Labyrinth GetLabyrinthWithShortestPathByPositions(
	PositionCell const& startPosition, 
	PositionCell const& endPosition, 
	Labyrinth& labyrinthWithoutShortestPath, 
	SearchSettings const& searchSettings
)
{
	Labyrinth labyrinth = labyrinthWithoutShortestPath;
	std::vector<PositionCell> offcetCell = (searchSettings == SearchSettings::VON_NEUMANN) ?
		OFFCET_CELL_VON_NEUMANN : OFFCET_CELL_MUR;

	if (!SpreadWaveInLabyrinth(labyrinth, startPosition, endPosition, offcetCell))
	{
		return labyrinthWithoutShortestPath;
	}

	std::stack<PositionCell> shortestPath = GetFromLabyrinthShortestPath(labyrinth, startPosition, endPosition, offcetCell);

	return SetShortestPathToLabyrinth(labyrinthWithoutShortestPath, shortestPath);
}

Labyrinth FindingShortestPathInLabyrinth(Labyrinth& labyrinth, SearchSettings const& searchSettings)
{
	ValidateLabyrinth(labyrinth);

	PositionCell start = GetPositionFromLabyrinthOf(LabyrinthCells::START, labyrinth);
	PositionCell end = GetPositionFromLabyrinthOf(LabyrinthCells::END, labyrinth);

	return GetLabyrinthWithShortestPathByPositions(start, end, labyrinth, searchSettings);
}

std::ofstream GetOutputFileStream(std::string const& filePath)
{
	std::ofstream file(filePath);
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open file for writing.");
	}
	return move(file);
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

void WriteLabyrinthInFile(std::string const& filePath, Labyrinth& labyrinth)
{
	std::ofstream file = GetOutputFileStream(filePath);

	for (auto& vectorOfCell : labyrinth)
	{
		for (auto& labyrinthCell : vectorOfCell)
		{
			file << InvertLabyrinthCellsTable.find(ToLabyrinthCells(labyrinthCell))->second;
		}
		file << std::endl;
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
	LabyrintInfo labyrinthInfo{};

	labyrinthInfo.bordersLabyrinth = GetBordersOfLabyrinthFromFile(filePath);

	labyrinthInfo.labyrinthSize.height = (labyrinthInfo.bordersLabyrinth.bottom.row - labyrinthInfo.bordersLabyrinth.top.row) + 1;
	labyrinthInfo.labyrinthSize.width = (labyrinthInfo.bordersLabyrinth.right.colum - labyrinthInfo.bordersLabyrinth.left.colum) + 1;

	if ((labyrinthInfo.labyrinthSize.height > MAX_LABYRINTH_SIZE) or (labyrinthInfo.labyrinthSize.width > MAX_LABYRINTH_SIZE))
	{
		throw std::out_of_range("The readable labyrinth is too large. Use labyrinth size 100x100.");
	}

	labyrinthInfo.labyrinthOffset.lengthTop = labyrinthInfo.bordersLabyrinth.top.row;
	labyrinthInfo.labyrinthOffset.lengthLeft = labyrinthInfo.bordersLabyrinth.left.colum;

	return labyrinthInfo;
}

void ArgumentsCountCheck(int argc)
{
	if (argc != 3 and argc != 4)
	{
		std::cout << "Usage: labyrinth.exe <input file> <output file> <setting for search>" << std::endl
			<< "\t<input file> - path to input file." << std::endl
			<< "\t<output file> - path to output file." << std::endl
			<< "\t(optional)<setting for search> - \"mur\" or \"von-neuman\". By default von-neuman search." << std::endl
			<< "\t\tmur - orthogonal and diagonal search." << std::endl
			<< "\t\tvon-neuman - only orthogonal search." << std::endl;

		throw std::invalid_argument("Invalid arguments count.");
	}
}

bool IsSearchSetting(std::string const& str)
{
	return (SearchSettingsTable.find(str) != SearchSettingsTable.end()) ? true : false;
}

void ValidateArguments(int argc, char* argv[])
{
	ArgumentsCountCheck(argc);
	
	if (argc == 4 and not IsSearchSetting(argv[3]))
	{
		throw std::invalid_argument("Search setting is not correct.");
	}
}

Labyrinth GetLabyrinthFromArgv(int argc, char* argv[])
{
	ValidateArguments(argc, argv);

	LabyrintInfo labyrinthInfo = GetLabyrinthInfoFromFile(argv[1]);

	if (labyrinthInfo.labyrinthSize.height == 1 and labyrinthInfo.labyrinthSize.width == 1)
	{
		throw std::length_error("There is no labyrinth in the file.");
	}

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

			if (fileCol < temp.size())
			{
				temp[fileCol - labyrinthInfo.labyrinthOffset.lengthLeft] = ToInt(LabyrinthCellsTable.find(labyrinthCell)->second);
			}

			fileCol++;
		}

		labyrinth.push_back(temp);
		fileRow++;
	}

	file.close();

	return labyrinth;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	try
	{	
		Labyrinth labyrinth = GetLabyrinthFromArgv(argc, argv);

		SearchSettings searchSettings = SearchSettings::VON_NEUMANN;
		if (argc == 4) searchSettings = SearchSettingsTable.find(argv[3])->second;

		Labyrinth labyrinthWithShortestPath = FindingShortestPathInLabyrinth(labyrinth, searchSettings);
		WriteLabyrinthInFile(argv[2], labyrinthWithShortestPath);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}