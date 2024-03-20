#include "Labyrinth.h"

void UpdateBorders(LabyrinthBorders& labyrinthBorders, CellPosition const& cellPosition)
{
	if (labyrinthBorders.left.y > cellPosition.y)
	{
		labyrinthBorders.left = cellPosition;
	}

	if (labyrinthBorders.bottom.x < cellPosition.x)
	{
		labyrinthBorders.bottom = cellPosition;
	}

	if (labyrinthBorders.right.y < cellPosition.y)
	{
		labyrinthBorders.right = cellPosition;
	}
}

LabyrinthBorders GetBordersOfLabyrinthFromStream(std::istream& inputStream)
{
	LabyrinthBorders borders{};
	std::string streamLine;
	bool isFirstWall = true;
	int16_t row = 0;

	while (std::getline(inputStream, streamLine))
	{
		int16_t col = 0;

		for (char const& labyrinthCell : streamLine)
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

	return borders;
}

LabyrinthInfo GetLabyrinthInfoFromStream(std::istream& inputStream)
{
	LabyrinthInfo labyrinthInfo{};

	labyrinthInfo.border = GetBordersOfLabyrinthFromStream(inputStream);

	labyrinthInfo.size.height = (labyrinthInfo.border.bottom.x - labyrinthInfo.border.top.x) + 1;
	labyrinthInfo.size.width = (labyrinthInfo.border.right.y - labyrinthInfo.border.left.y) + 1;

	if ((labyrinthInfo.size.height > MAX_LABYRINTH_SIZE) || 
		(labyrinthInfo.size.width > MAX_LABYRINTH_SIZE))
	{
		throw std::out_of_range("The readable labyrinth is too large. Use labyrinth size 100x100.");
	}

	labyrinthInfo.offset.top = labyrinthInfo.border.top.x;
	labyrinthInfo.offset.top = labyrinthInfo.border.left.y;

	return labyrinthInfo;
}

LabyrinthCells ToLabyrinthCells(int16_t labyrinthCell)
{
	return static_cast<LabyrinthCells>(labyrinthCell);
}

int16_t ToInt(LabyrinthCells labyrinthCell)
{
	return static_cast<int16_t>(labyrinthCell);
}

void ValidateLabyrinth(LabyrinthMatrix const& labyrinthMatrix)
{
	LabyrinthVector result;
	for (auto& labyrinthVector : labyrinthMatrix)
	{
		result.insert(result.end(), labyrinthVector.begin(), labyrinthVector.end());
	}

	using namespace boost::algorithm;
	if (!one_of_equal(result.begin(), result.end(), ToInt(LabyrinthCells::START)) ||
		!one_of_equal(result.begin(), result.end(), ToInt(LabyrinthCells::END)))
	{
		throw std::out_of_range("The starting/end point is incorrect.");
	}
}

LabyrinthMatrix GetLabyrinthFromStream(std::istream& inputStream)
{
	LabyrinthInfo labyrinthInfo = GetLabyrinthInfoFromStream(inputStream);
	LabyrinthMatrix labyrinthMatrix;
	std::string labyrinthLine;
	size_t fileRow = 0;

	while (std::getline(inputStream, labyrinthLine))
	{
		if (fileRow < labyrinthInfo.offset.top)
		{
			fileRow++;
			continue;
		}

		if ((fileRow - labyrinthInfo.offset.top) == labyrinthInfo.size.height) break;

		std::vector<int16_t> temp(labyrinthInfo.size.width, ToInt(LabyrinthCells::BLANK));
		size_t fileColumn = 0;

		for (char const& cell : labyrinthLine)
		{
			if (fileColumn < labyrinthInfo.offset.left)
			{
				fileColumn++;
				continue;
			}

			if (fileColumn < temp.size())
			{
				temp[fileColumn - labyrinthInfo.offset.left] = ToInt(LABYRINTH_CELLS_TABLE.find(cell)->second);
			}

			fileColumn++;
		}

		labyrinthMatrix.push_back(temp);
		fileRow++;
	}

	return labyrinthMatrix;
}

CellPosition GetPositionOf(LabyrinthCells labyrinthCells, LabyrinthMatrix const& labyrinth)
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

void SetShortestPathToLabyrinth(
	LabyrinthMatrix& labyrinthMatrix,
	CellPosition const& startWave,
	CellPosition const& endWave
)
{
	int16_t waveLength = labyrinthMatrix[endWave.x][endWave.y];
	CellPosition endPosition = GetPositionOf(LabyrinthCells::END, labyrinthMatrix);

	while (waveLength > 0)
	{
		for (size_t vicinity = 0; vicinity < 4; ++vicinity)
		{
			int16_t x = endPosition.x + CELLS_OFFSET[vicinity].x;
			int16_t y = endPosition.y + CELLS_OFFSET[vicinity].y;

			if (x >= 0 && x < labyrinthMatrix.size() &&
				y >= 0 && y < labyrinthMatrix[0].size() &&
				labyrinthMatrix[x][y] == waveLength)
			{
				endPosition.x += CELLS_OFFSET[vicinity].x;
				endPosition.y += CELLS_OFFSET[vicinity].y;
				labyrinthMatrix[x][y] = ToInt(LabyrinthCells::PATH);
				waveLength--;
				break;
			}
		}
	}
}

std::vector<CellPosition> GetLabeledCellsAround(
	LabyrinthMatrix& labyrinth,
	CellPosition currentCell,
	bool& labyrinthEndFound
)
{
	std::vector<CellPosition> cellsLabeled;

	for (size_t vicinity = 0; vicinity < 4; ++vicinity)
	{
		int16_t x = currentCell.x + CELLS_OFFSET[vicinity].x;
		int16_t y = currentCell.y + CELLS_OFFSET[vicinity].y;

		if ((x >= 0 && x < labyrinth.size()) && (y >= 0 && y < labyrinth.front().size()))
		{
			if (labyrinth[x][y] == ToInt(LabyrinthCells::END))
			{
				labyrinthEndFound = true;
				return { {currentCell.x, currentCell.y} };
			}

			if (labyrinth[x][y] == ToInt(LabyrinthCells::BLANK))
			{
				labyrinth[x][y] = labyrinth[currentCell.x][currentCell.y] + 1;
				cellsLabeled.push_back({ x, y });
			}
		}
	}

	return cellsLabeled;
}

bool SpreadWaveInLabyrinth(LabyrinthMatrix& labyrinthMatrix)
{
	bool isLabyrinthEndFound = false;

	CellPosition start = GetPositionOf(LabyrinthCells::START, labyrinthMatrix);

	std::vector<CellPosition> cellsForCheck =
		GetLabeledCellsAround(labyrinthMatrix, start, isLabyrinthEndFound);

	while (!cellsForCheck.empty())
	{
		std::vector<CellPosition> nextCellsForCheck = GetLabeledCellsAround(
			labyrinthMatrix, cellsForCheck.front(), isLabyrinthEndFound
		);

		if (isLabyrinthEndFound)
		{
			SetShortestPathToLabyrinth(labyrinthMatrix, start, nextCellsForCheck.front());
			return true;
		}

		cellsForCheck.insert(cellsForCheck.end(), nextCellsForCheck.begin(), nextCellsForCheck.end());
		cellsForCheck.erase(cellsForCheck.begin());
	}

	return false;
}

LabyrinthMatrix GetLabyrinthWithShortestPath(LabyrinthMatrix const& labyrinthMatrix)
{
	LabyrinthMatrix labyrinthMatrixCopy(labyrinthMatrix);

	bool isLabyrinthEndFound = SpreadWaveInLabyrinth(labyrinthMatrixCopy);

	return isLabyrinthEndFound ? labyrinthMatrixCopy : labyrinthMatrix;
}

std::ostream& operator<<(std::ostream& os, LabyrinthMatrix const& labyrinthMatrix)
{
	for (size_t i = 0; i < labyrinthMatrix.size(); ++i)
	{
		for (size_t j = 0; j < labyrinthMatrix[i].size(); ++j)
		{
			os << INVERT_LABYRINTH_CELLS_TABLE.find(ToLabyrinthCells(labyrinthMatrix[i][j]))->second;
		}
		os << std::endl;
	}
	return os;
}