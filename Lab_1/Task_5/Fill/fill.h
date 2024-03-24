#include <array>
#include <set>
#include <string>
#include <iostream>
#include <istream>
#include <unordered_map>
#include <algorithm>
#include <functional>

namespace
{
	inline constexpr int16_t MAX_SIZE_OUTLINE_AREA = 100;

	struct CellCoordinate
	{
		int16_t x;
		int16_t y;
	};

	using OutlinesLine = std::vector<int16_t>;
	using Outlines = std::vector<OutlinesLine>;
	using LabeledCells = std::vector<CellCoordinate>;

	enum class OutlineCells
	{
		BLANK = 0,
		FILL,
		START,
		WALL,
	};

	static std::unordered_map<char, OutlineCells> const OUTLINE_CELLS_TABLE = {
			{' ', OutlineCells::BLANK},
			{'#', OutlineCells::WALL},
			{'O', OutlineCells::START},
			{'.', OutlineCells::FILL},
	};

	static std::unordered_map<OutlineCells, char> const INVERT_OUTLINE_CELLS_TABLE = {
			{OutlineCells::BLANK, ' '},
			{OutlineCells::WALL, '#'},
			{OutlineCells::START, 'O'},
			{OutlineCells::FILL, '.'},
	};

	static std::vector<CellCoordinate> const MUR_OFFSET = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0}
	};
}

OutlineCells ToOutlineCells(int16_t cell);

int16_t ToInt(OutlineCells cell);

Outlines GetOutlinesFromStream(std::istream& inputStream);

LabeledCells GetCellsForFillAround(Outlines& outlines, CellCoordinate cell);

void FillOutlines(Outlines& outlines);

void ValidateOutlines(Outlines const& outlines);

std::vector<CellCoordinate> GetCellsCoordinateOf(OutlineCells cellType, Outlines const& outlines);

std::ostream& operator<<(std::ostream& os, Outlines const& labyrinth);