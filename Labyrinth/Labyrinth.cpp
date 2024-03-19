#include "Labyrinth.h"

LabyrinthCells ToLabyrinthCells(int16_t labyrinthCell)
{
	return static_cast<LabyrinthCells>(labyrinthCell);
}

int16_t ToInt(LabyrinthCells labyrinthCell)
{
	return static_cast<int8_t>(labyrinthCell);
}

void UpdateBorders(LabyrinthBorders& labyrinthBorders, CellPosition const& cellPosition)
{
	if (labyrinthBorders.left.column > cellPosition.column)
	{
		labyrinthBorders.left = cellPosition;
	}

	if (labyrinthBorders.bottom.row < cellPosition.row)
	{
		labyrinthBorders.bottom = cellPosition;
	}

	if (labyrinthBorders.right.column < cellPosition.column)
	{
		labyrinthBorders.right = cellPosition;
	}
}

CellPosition GetPositionOf(LabyrinthCells labyrinthCells, Labyrinth const& labyrinth)
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
	std::vector<int16_t> vectLabyrinth;
	for (auto& ñellLine : labyrinth) vectLabyrinth.insert(vectLabyrinth.end(), ñellLine.begin(), ñellLine.end());

	if (!boost::algorithm::one_of(vectLabyrinth.begin(), vectLabyrinth.end(), IsEndPosition) or
		!boost::algorithm::one_of(vectLabyrinth.begin(), vectLabyrinth.end(), IsStartPosition))
	{
		throw std::out_of_range("The starting/end point is incorrect.");
	}
}

std::vector<CellPosition> GetLabeledCellsAround(
	CellPosition currentCell,
	Labyrinth& labyrinth,
	std::vector<CellPosition> const& cellsChecked,
	bool& labyrinthEndFound
)
{
	std::vector<CellPosition> cellsLabeled;

	for (size_t vicinity = 0; vicinity < cellsChecked.size(); ++vicinity)
	{
		int16_t x = currentCell.row + cellsChecked[vicinity].row;
		int16_t y = currentCell.column + cellsChecked[vicinity].column;

		if (x >= 0 and x < labyrinth.size() and
			y >= 0 and y < labyrinth[0].size() and
			labyrinth[x][y] == ToInt(LabyrinthCells::END))
		{
			labyrinthEndFound = true;
			return { {currentCell.row, currentCell.column} };
		}

		if (x >= 0 and x < labyrinth.size() and
			y >= 0 and y < labyrinth[0].size() and
			labyrinth[x][y] == ToInt(LabyrinthCells::BLANK))
		{
			labyrinth[x][y] = labyrinth[currentCell.row][currentCell.column] + 1;
			cellsLabeled.push_back({ x,y });
		}
	}

	return cellsLabeled;
}

void SetShortestPathToLabyrinth(
	Labyrinth& labyrinth,
	CellPosition const& startWave,
	CellPosition const& endWave,
	std::vector<CellPosition> const& cellsChecked
)
{
	int16_t waveLength = labyrinth[endWave.row][endWave.column];
	CellPosition endPosition = GetPositionOf(LabyrinthCells::END, labyrinth);

	while (waveLength > 0)
	{
		for (size_t vicinity = 0; vicinity < cellsChecked.size(); ++vicinity)
		{
			int16_t x = endPosition.row + cellsChecked[vicinity].row;
			int16_t y = endPosition.column + cellsChecked[vicinity].column;

			if (x >= 0 and x < labyrinth.size() and
				y >= 0 and y < labyrinth[0].size() and
				labyrinth[x][y] == waveLength)
			{
				endPosition.row += cellsChecked[vicinity].row;
				endPosition.column += cellsChecked[vicinity].column;
				labyrinth[x][y] = ToInt(LabyrinthCells::PATH);
				waveLength--;
				break;
			}
		}
	}
}

void SpreadWaveInLabyrinth(
	Labyrinth& labyrinth,
	CellPosition start,
	bool& labyrinthEndFound,
	std::vector<CellPosition> const& cellsChecked
)
{
	labyrinth[start.row][start.column] = 0;
	std::vector<CellPosition> cellsForCheck = GetLabeledCellsAround(start, labyrinth, cellsChecked, labyrinthEndFound);

	while (!cellsForCheck.empty())
	{
		std::vector<CellPosition> nextCellsForCheck = GetLabeledCellsAround(cellsForCheck[0], labyrinth, cellsChecked, labyrinthEndFound);

		if (labyrinthEndFound)
		{
			SetShortestPathToLabyrinth(labyrinth, start, nextCellsForCheck[0], cellsChecked);
			return;
		}

		cellsForCheck.insert(cellsForCheck.end(), nextCellsForCheck.begin(), nextCellsForCheck.end());
		cellsForCheck.erase(cellsForCheck.begin());
	}
}

Labyrinth GetLabyrinthWithShortestPath(Labyrinth const& labyrinthWithoutShortestPath, SearchSettings const& searchSettings)
{
	ValidateLabyrinth(labyrinthWithoutShortestPath);

	Labyrinth labyrinth = labyrinthWithoutShortestPath;
	CellPosition start = GetPositionOf(LabyrinthCells::START, labyrinthWithoutShortestPath);
	bool labyrinthEndFound = false;

	std::vector<CellPosition> cellsChecked = (searchSettings == SearchSettings::VON_NEUMANN) ?
		OFFSET_CELL_VON_NEUMANN : OFFSET_CELL_MUR;

	SpreadWaveInLabyrinth(labyrinth, start, labyrinthEndFound, cellsChecked);
	 
	return labyrinthEndFound ? labyrinth : labyrinthWithoutShortestPath;
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

void WriteLabyrinthInFile(std::string const& filePath, Labyrinth const& labyrinth)
{
	std::ofstream file = GetOutputFileStream(filePath);

	for (auto& vectorOfCell : labyrinth)
	{
		for (auto& labyrinthCell : vectorOfCell)
		{
			auto const& it = INVERT_LABYRINTH_CELLS_TABLE.find(ToLabyrinthCells(labyrinthCell));

			if (it != INVERT_LABYRINTH_CELLS_TABLE.end()) file << it->second;
			else file << INVERT_LABYRINTH_CELLS_TABLE.find(LabyrinthCells::BLANK)->second;
		}
		file << std::endl;
	}
}

LabyrinthBorders GetBordersOfLabyrinthFromFile(std::string const& filePath)
{
	std::ifstream file = GetInputFileStream(filePath);

	LabyrinthBorders borders{};

	std::string fileLine;
	bool isFirstWall = true;
	int16_t row = 0;

	while (std::getline(file, fileLine))
	{
		int16_t col = 0;
		for (char const& labyrinthCell : fileLine)
		{
			if (LABYRINTH_CELLS_TABLE.find(labyrinthCell)->second == LabyrinthCells::WALL)
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

LabyrinthInfo GetLabyrinthInfoFromFile(std::string const& filePath)
{
	LabyrinthInfo labyrinthInfo{};

	labyrinthInfo.labyrinthBorders = GetBordersOfLabyrinthFromFile(filePath);

	labyrinthInfo.labyrinthSize.height = (labyrinthInfo.labyrinthBorders.bottom.row - labyrinthInfo.labyrinthBorders.top.row) + 1;
	labyrinthInfo.labyrinthSize.width = (labyrinthInfo.labyrinthBorders.right.column - labyrinthInfo.labyrinthBorders.left.column) + 1;

	if ((labyrinthInfo.labyrinthSize.height > MAX_LABYRINTH_SIZE) or (labyrinthInfo.labyrinthSize.width > MAX_LABYRINTH_SIZE))
	{
		throw std::out_of_range("The readable labyrinth is too large. Use labyrinth size 100x100.");
	}

	labyrinthInfo.labyrinthOffset.offsetTop = labyrinthInfo.labyrinthBorders.top.row;
	labyrinthInfo.labyrinthOffset.offsetLeft = labyrinthInfo.labyrinthBorders.left.column;

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
	return (SEARCH_SETTINGS_TABLE.find(str) != SEARCH_SETTINGS_TABLE.end()) ? true : false;
}

void ValidateArguments(int argc, char* argv[])
{
	ArgumentsCountCheck(argc);
	
	if (argc == 4 and !IsSearchSetting(argv[3]))
	{
		throw std::invalid_argument("Search setting is not correct.");
	}
}

Labyrinth GetLabyrinthFromArgv(int argc, char* argv[])
{
	ValidateArguments(argc, argv);

	LabyrinthInfo labyrinthInfo = GetLabyrinthInfoFromFile(argv[1]);

	if (labyrinthInfo.labyrinthSize.height == 1 and labyrinthInfo.labyrinthSize.width == 1)
	{
		throw std::length_error("There is no labyrinth in the file.");
	}

	return GetLabyrinthFromFile(argv[1], labyrinthInfo);
}

SearchSettings GetSearchSetting(int argc, char* argv[])
{
	if (argc == 4)
	{
		auto const& it = SEARCH_SETTINGS_TABLE.find(argv[3]);

		if (it != SEARCH_SETTINGS_TABLE.end()) return it->second;
	}

	return SearchSettings::VON_NEUMANN;
}

Labyrinth GetLabyrinthFromFile(std::string const& filePath, LabyrinthInfo const& labyrinthInfo)
{
	Labyrinth labyrinth;
	std::ifstream fileStream = GetInputFileStream(filePath);
	std::string fileLine;
	size_t fileRow = 0;

	while (std::getline(fileStream, fileLine))
	{
		if (fileRow < labyrinthInfo.labyrinthOffset.offsetTop)
		{
			fileRow++;
			continue;
		}

		if ((fileRow - labyrinthInfo.labyrinthOffset.offsetTop) == labyrinthInfo.labyrinthSize.height) break;

		std::vector<int16_t> temp(labyrinthInfo.labyrinthSize.width, ToInt(LabyrinthCells::BLANK));
		size_t fileColumn = 0;

		for (char const& cell : fileLine)
		{
			if (fileColumn < labyrinthInfo.labyrinthOffset.offsetLeft)
			{
				fileColumn++;
				continue;
			}

			if (fileColumn < temp.size())
			{
				temp[fileColumn - labyrinthInfo.labyrinthOffset.offsetLeft] = ToInt(LABYRINTH_CELLS_TABLE.find(cell)->second);
			}

			fileColumn++;
		}

		labyrinth.push_back(temp);
		fileRow++;
	}

	fileStream.close();
	
	return labyrinth;
}
