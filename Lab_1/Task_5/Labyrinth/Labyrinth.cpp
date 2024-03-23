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

LabyrinthBorders GetLabyrinthBorders(Labyrinth const& labyrinth)
{
	LabyrinthBorders labyrinthBorders{};
	bool isFirstWall = true;

	for (int32_t x = 0; x < labyrinth.size(); x++)
	{
		for (int32_t y = 0; y < labyrinth[x].size(); y++)
		{
			if (labyrinth[x][y] == ToInt(LabyrinthCells::WALL))
			{
				if (isFirstWall)
				{
					labyrinthBorders.top = { x, y };
					labyrinthBorders.left = { x, y };
					labyrinthBorders.right = { x, y };
					labyrinthBorders.bottom = { x, y };

					isFirstWall = false;
				}
				else
				{
					UpdateBorders(labyrinthBorders, { x, y });
				}
			}
		}
	}

	return labyrinthBorders;
}

void EraseOffsetsFromLabyrinth(Labyrinth& labyrinth)
{
	if (labyrinth.size() == 0)
	{
		throw std::length_error("There is no labyrinth in the file.");
	}

	LabyrinthBorders labyrinthBorders = GetLabyrinthBorders(labyrinth);

	size_t labyrinthHeight = (labyrinthBorders.bottom.x - labyrinthBorders.top.x) + 1;
	size_t labyrinthWidth = (labyrinthBorders.right.y - labyrinthBorders.left.y) + 1;

	if ((labyrinthHeight > MAX_LABYRINTH_SIZE) || (labyrinthWidth > MAX_LABYRINTH_SIZE))
	{
		throw std::out_of_range("The readable labyrinth is too large. Use labyrinth size 100x100.");
	}

	for (size_t row = 0; row < labyrinthHeight; row++)
	{
		labyrinth[row].erase(
			labyrinth[row].begin(),
			labyrinth[row].begin() + labyrinthBorders.left.y
		);
	}
}

LabyrinthCells ToLabyrinthCells(int32_t labyrinthCell)
{
	return static_cast<LabyrinthCells>(labyrinthCell);
}

int32_t ToInt(LabyrinthCells labyrinthCell)
{
	return static_cast<int32_t>(labyrinthCell);
}

void ValidateLabyrinth(Labyrinth const& labyrinth)
{
	LabyrinthLine labyrinthLine;
	for (auto const& line : labyrinth)
	{
		labyrinthLine.insert(labyrinthLine.end(), line.begin(), line.end());
	}

	using namespace boost::algorithm;
	if (!one_of_equal(labyrinthLine.begin(), labyrinthLine.end(), ToInt(LabyrinthCells::START)) ||
		!one_of_equal(labyrinthLine.begin(), labyrinthLine.end(), ToInt(LabyrinthCells::END)))
	{
		throw std::logic_error("The starting/end point is incorrect.");
	}
}

bool IsBlankCell(int32_t cell)
{ 
	return cell == ToInt(LabyrinthCells::BLANK); 
}

bool IsGreaterZero(int32_t number)
{
	return number > 0;
}

Labyrinth GetLabyrinthFromStream(std::istream& inputStream)
{
	Labyrinth labyrinth;
	std::string labyrinthLine;

	while (std::getline(inputStream, labyrinthLine))
	{
		LabyrinthLine labyrinthVector;

		for (char const& cell : labyrinthLine)
		{
			labyrinthVector.push_back(ToInt(LABYRINTH_CELLS_TABLE.find(cell)->second));
		}

		if (std::all_of(labyrinthVector.begin(), labyrinthVector.end(), IsBlankCell))
		{
			continue;
		}

		labyrinth.push_back(labyrinthVector);
	}

	return labyrinth;
}

Labyrinth GetLabyrinthWithoutOffsetsFromStream(std::istream& inputStream)
{
	Labyrinth labyrinth = GetLabyrinthFromStream(inputStream);
	EraseOffsetsFromLabyrinth(labyrinth);
	return labyrinth;
}

CellPosition GetPositionOf(LabyrinthCells labyrinthCells, Labyrinth const& labyrinth)
{
	for (int32_t i = 0; i < labyrinth.size(); i++)
	{
		for (int32_t j = 0; j < labyrinth[i].size(); j++)
		{
			if (labyrinth[i][j] == ToInt(labyrinthCells)) return { i, j };
		}
	}

	throw std::invalid_argument("Cell not found.");
}

LabeledCells GetLabeledCellsAround(
	Labyrinth& labyrinth, 
	CellPosition currentCell, 
	bool& isPathExist
)
{
	LabeledCells cellsLabeled;

	for (size_t direction = 0; direction < 4; ++direction)
	{
		int32_t x = currentCell.x + MUR_OFFSET[direction].x;
		int32_t y = currentCell.y + MUR_OFFSET[direction].y;

		if (x >= 0 && x < labyrinth.size() && 
			y >= 0 && y < labyrinth[x].size())
		{
			if (labyrinth[x][y] == ToInt(LabyrinthCells::END))
			{
				isPathExist = true;
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

void SetShortestPathToLabyrinth(Labyrinth& labyrinth, CellPosition const& endWave)
{
	int32_t waveLength = labyrinth[endWave.x][endWave.y];
	CellPosition endPosition = GetPositionOf(LabyrinthCells::END, labyrinth);

	while (waveLength > 0)
	{
		for (size_t direction = 0; direction < 4; ++direction)
		{
			int32_t x = endPosition.x + MUR_OFFSET[direction].x;
			int32_t y = endPosition.y + MUR_OFFSET[direction].y;

			if (x >= 0 && x < labyrinth.size() &&
				y >= 0 && y < labyrinth[x].size() &&
				labyrinth[x][y] == waveLength)
			{
				endPosition.x += MUR_OFFSET[direction].x;
				endPosition.y += MUR_OFFSET[direction].y;
				labyrinth[x][y] = ToInt(LabyrinthCells::PATH);
				waveLength--;
				break;
			}
		}
	}

	for (auto& labyrinthLine : labyrinth)
	{
		std::ranges::replace_if(
			labyrinthLine,
			IsGreaterZero, 
			ToInt(LabyrinthCells::BLANK)
		);
	}
}

bool IsPathInLabyrinthFound(Labyrinth& labyrinth)
{
	bool isPathExist = false;
	CellPosition start = GetPositionOf(LabyrinthCells::START, labyrinth);

	LabeledCells cellsForCheck =
		GetLabeledCellsAround(labyrinth, start, isPathExist);

	while (!cellsForCheck.empty())
	{
		LabeledCells nextCellsForCheck = GetLabeledCellsAround(
			labyrinth, cellsForCheck.front(), isPathExist
		);

		if (isPathExist)
		{
			SetShortestPathToLabyrinth(labyrinth, nextCellsForCheck.front());
			return true;
		}

		cellsForCheck.insert(
			cellsForCheck.end(), 
			nextCellsForCheck.begin(), 
			nextCellsForCheck.end()
		);
		cellsForCheck.erase(cellsForCheck.begin());
	}

	return false;
}

Labyrinth GetLabyrinthWithShortestPath(Labyrinth const& labyrinthWithoutPath)
{
	Labyrinth labyrinth(labyrinthWithoutPath);
	return IsPathInLabyrinthFound(labyrinth) ? labyrinth : labyrinthWithoutPath;
}

std::ostream& operator<<(std::ostream& os, Labyrinth const& labyrinth)
{
	for (size_t i = 0; i < labyrinth.size(); ++i)
	{
		for (size_t j = 0; j < labyrinth[i].size(); ++j)
		{
			os << INVERT_LABYRINTH_CELLS_TABLE.find(ToLabyrinthCells(labyrinth[i][j]))->second;
		}
		os << std::endl;
	}
	return os;
}