#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

#include "boost/algorithm/cxx11/one_of.hpp"

inline constexpr size_t MAX_LABYRINTH_SIZE = 100;

using LabyrinthVector = std::vector<int16_t>;
using LabyrinthMatrix = std::vector<LabyrinthVector>;

enum class LabyrinthCells
{
	PATH = -4,
	END,
	BLANK,
	WALL,
	START
};

struct CellPosition
{
	int16_t x;
	int16_t y;
};

static std::unordered_map<char, LabyrinthCells> const LABYRINTH_CELLS_TABLE = {
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

static std::vector<CellPosition> const CELLS_OFFSET = {
	{0, 1},
	{1, 0},
	{0, -1},
	{-1, 0}
};

struct LabyrinthOffset
{
	size_t top;
	size_t left;
};

struct LabyrinthSize
{
	int16_t height;
	int16_t width;
};

struct LabyrinthBorders
{
	CellPosition top;
	CellPosition left;
	CellPosition right;
	CellPosition bottom;
};

struct LabyrinthInfo
{
	//данные могут быть не согласованными, так как данные дублируются 
	LabyrinthBorders border;
	LabyrinthOffset offset;
	LabyrinthSize size;
};

bool SpreadWaveInLabyrinth(LabyrinthMatrix& labyrinth);

void ValidateLabyrinth(LabyrinthMatrix const& labyrinthMatrix);

void SetShortestPathToLabyrinth(LabyrinthMatrix& labyrinth, CellPosition const& startWave, CellPosition const& endWave);

void UpdateBorders(LabyrinthBorders& labyrinthBorders, CellPosition const& cellPosition);

LabyrinthMatrix GetLabyrinthFromStream(std::istream& inputStream);

LabyrinthMatrix GetLabyrinthWithShortestPath(LabyrinthMatrix const& labyrinthMatrix);

CellPosition GetPositionOf(LabyrinthCells labyrinthCells, LabyrinthMatrix const& labyrinth);

std::vector<CellPosition> GetLabeledCellsAround(LabyrinthMatrix& labyrinth, CellPosition currentCell, bool& labyrinthEndFound);

LabyrinthCells ToLabyrinthCells(int16_t labyrinthCell);

int16_t ToInt(LabyrinthCells labyrinthCell);

LabyrinthBorders GetBordersOfLabyrinthFromStream(std::istream& inputStream);

LabyrinthInfo GetLabyrinthInfoFromStream(std::istream& inputStream);

std::ostream& operator<<(std::ostream& os, LabyrinthMatrix const& labyrinthMatrix);