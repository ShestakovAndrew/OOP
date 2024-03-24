#include "fill.h"

OutlineCells ToOutlineCells(int16_t cell)
{
	return static_cast<OutlineCells>(cell);
}

int16_t ToInt(OutlineCells cell)
{
	return static_cast<int16_t>(cell);
}

Outlines GetOutlinesFromStream(std::istream& inputStream)
{
	bool isInputWasCutted = false;
	Outlines outlines;
	std::string outlineLineStr;
	size_t rowCount = 0;

	while (std::getline(inputStream, outlineLineStr))
	{
		if (rowCount >= MAX_SIZE_OUTLINE_AREA)
		{
			isInputWasCutted = true;
			break;
		}

		OutlinesLine outlinesLine;
		size_t maxSizeOutlinesLine = outlineLineStr.size();

		if (outlineLineStr.size() > MAX_SIZE_OUTLINE_AREA)
		{
			isInputWasCutted = true;
			maxSizeOutlinesLine = MAX_SIZE_OUTLINE_AREA;
		}

		for (size_t i = 0; i < maxSizeOutlinesLine; i++)
		{
			outlinesLine.push_back(ToInt(OUTLINE_CELLS_TABLE.find(outlineLineStr[i])->second));
		}

		outlines.push_back(outlinesLine);
		rowCount++;
	}

	if (isInputWasCutted)
	{
		std::cout << "Input file was cutted." << std::endl;
	}

	return outlines;
}

LabeledCells GetCellsForFillAround(Outlines& outlines, CellCoordinate cell)
{
	LabeledCells cellsForCheck;

	for (size_t direction = 0; direction < 4; ++direction)
	{
		int16_t x = cell.x + MUR_OFFSET[direction].x;
		int16_t y = cell.y + MUR_OFFSET[direction].y;

		if ((x >= 0 && x < MAX_SIZE_OUTLINE_AREA) && (y >= 0 && y < MAX_SIZE_OUTLINE_AREA))
		{
			if (outlines.size() <= x)
			{
				OutlinesLine outlinesLine(outlines[x - 1].size(), ToInt(OutlineCells::BLANK));
				outlines.push_back(outlinesLine);
			}

			if (outlines[x].size() <= y)
			{
				outlines[x].push_back(ToInt(OutlineCells::FILL));
				cellsForCheck.push_back({ x, y });
				continue;
			}

			if (outlines[x][y] == ToInt(OutlineCells::BLANK))
			{
				outlines[x][y] = ToInt(OutlineCells::FILL);
				cellsForCheck.push_back({ x, y });
				continue;
			}
		}
	}

	return cellsForCheck;
}

inline bool IsStartCell(uint16_t cell)
{
	return cell == ToInt(OutlineCells::START);
}

void FillOutlines(Outlines& outlines)
{
	std::vector<CellCoordinate> startCoords = GetCellsCoordinateOf(OutlineCells::START, outlines);

	for (auto const& startCoord : startCoords)
	{
		LabeledCells cellsForCheck = GetCellsForFillAround(outlines, startCoord);

		while (!cellsForCheck.empty())
		{
			LabeledCells nextCellsForCheck = GetCellsForFillAround(outlines, cellsForCheck.front());

			cellsForCheck.insert(
				cellsForCheck.end(),
				nextCellsForCheck.begin(),
				nextCellsForCheck.end()
			);

			cellsForCheck.erase(cellsForCheck.begin());
		}
	}
}

void ValidateOutlines(Outlines const& outlines)
{
	if (outlines.empty())
	{
		throw std::length_error("File empty to fill outlines.");
	}

	OutlinesLine outlinesLine;
	for (auto const& line : outlines)
	{
		outlinesLine.insert(outlinesLine.end(), line.begin(), line.end());
	}

	if (!std::any_of(outlinesLine.begin(), outlinesLine.end(), IsStartCell))
	{
		throw std::invalid_argument("No start point to fill outlines.");
	}
}

std::vector<CellCoordinate> GetCellsCoordinateOf(OutlineCells cellType, Outlines const& outlines)
{
	std::vector<CellCoordinate> cellsCoordinate;

	for (uint8_t i = 0; i < outlines.size(); i++)
	{
		for (uint8_t j = 0; j < outlines[i].size(); j++)
		{
			if (outlines[i][j] == ToInt(cellType)) cellsCoordinate.push_back({ i, j });
		}
	}

	return cellsCoordinate;
}

std::ostream& operator<<(std::ostream& os, Outlines const& outlines)
{
	for (size_t i = 0; i < outlines.size(); ++i)
	{
		for (size_t j = 0; j < outlines[i].size(); ++j)
		{
			os << INVERT_OUTLINE_CELLS_TABLE.find(ToOutlineCells(outlines[i][j]))->second;
		}
		os << std::endl;
	}
	return os;
}

