#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

#include "boost/algorithm/cxx11/one_of.hpp"

namespace
{
	inline constexpr size_t MAX_LABYRINTH_SIZE = 100;

	struct CellPosition
	{
		int32_t x;
		int32_t y;
	};

	struct LabyrinthBorders
	{
		CellPosition top;
		CellPosition left;
		CellPosition right;
		CellPosition bottom;
	};

	using LabyrinthLine = std::vector<int32_t>;
	using Labyrinth = std::vector<LabyrinthLine>;
	using LabeledCells = std::vector<CellPosition>;

	enum class LabyrinthCells
	{
		PATH = -4,
		END,
		BLANK,
		WALL,
		START
	};

	static std::unordered_map<int32_t, LabyrinthCells> const LABYRINTH_CELLS_TABLE = {
			{' ', LabyrinthCells::BLANK},
			{'#', LabyrinthCells::WALL},
			{'A', LabyrinthCells::START},
			{'B', LabyrinthCells::END},
			{'.', LabyrinthCells::PATH},
	};

	static std::unordered_map<LabyrinthCells, char> const INVERT_LABYRINTH_CELLS_TABLE = {
			{LabyrinthCells::BLANK, ' '},
			{LabyrinthCells::WALL, '#'},
			{LabyrinthCells::START, 'A'},
			{LabyrinthCells::END, 'B'},
			{LabyrinthCells::PATH, '.'},
	};

	static std::vector<CellPosition> const MUR_OFFSET = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0}
	};
}

bool IsPathInLabyrinthFound(Labyrinth& labyrinth);

bool IsBlankCell(int32_t cell);

bool IsGreaterZero(int32_t number);

void ValidateLabyrinth(Labyrinth const& labyrinth);

void SetShortestPathToLabyrinth(Labyrinth& labyrinth, CellPosition const& endWave);

void UpdateBorders(LabyrinthBorders& labyrinthBorders, CellPosition const& cellPosition);

void EraseOffsetsFromLabyrinth(Labyrinth& labyrinth);

Labyrinth GetLabyrinthFromStream(std::istream& inputStream);

Labyrinth GetLabyrinthWithoutOffsetsFromStream(std::istream& inputStream);

Labyrinth GetLabyrinthWithShortestPath(Labyrinth const& labyrinth);

CellPosition GetPositionOf(LabyrinthCells labyrinthCells, Labyrinth const& labyrinth);

LabeledCells GetLabeledCellsAround(
	Labyrinth& labyrinth, 
	CellPosition currentCell, 
	bool& isPathExist
);

LabyrinthCells ToLabyrinthCells(int32_t labyrinthCell);

int32_t ToInt(LabyrinthCells labyrinthCell);

LabyrinthBorders GetLabyrinthBorders(Labyrinth const& labyrinth);

std::ostream& operator<<(std::ostream& os, Labyrinth const& labyrinth);