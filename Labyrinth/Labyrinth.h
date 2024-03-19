#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <windows.h>

#include "boost/algorithm/cxx11/one_of.hpp"

const size_t MAX_LABYRINTH_SIZE = 100;
using Labyrinth = std::vector<std::vector<int16_t>>;

struct CellPosition
{
	int16_t row;
	int16_t column;
};

struct LabyrinthOffset
{
	size_t offsetTop;
	size_t offsetLeft;
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
	LabyrinthBorders labyrinthBorders;
	LabyrinthOffset labyrinthOffset;
	LabyrinthSize labyrinthSize;
};

static std::vector<CellPosition> const OFFSET_CELL_MUR = {
	{-1, -1},
	{-1, 1},
	{1, -1},
	{1, 1},
	{0, 1},
	{1, 0},
	{0, -1},
	{-1, 0}
};

static std::vector<CellPosition> const OFFSET_CELL_VON_NEUMANN = {
	{0, 1},
	{1, 0},
	{0, -1},
	{-1, 0}
};

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

static std::unordered_map<std::string, SearchSettings> const SEARCH_SETTINGS_TABLE = {
		{"mur", SearchSettings::MUR},
		{"von-neumann", SearchSettings::VON_NEUMANN},
};

LabyrinthCells ToLabyrinthCells(int16_t labyrinthCell);

int16_t ToInt(LabyrinthCells labyrinthCell);

void UpdateBorders(LabyrinthBorders& labyrinthBorders, CellPosition const& cellPosition);

bool IsStartPosition(int16_t cell);

bool IsEndPosition(int16_t cell);

void ValidateLabyrinth(Labyrinth const& labyrinth);

void SetShortestPathToLabyrinth(Labyrinth& labyrinth, CellPosition const& startWave, CellPosition const& endWave, std::vector<CellPosition> const& cellsChecked);

void SpreadWaveInLabyrinth(Labyrinth& labyrinth, CellPosition start, bool& labyrinthEndFound, std::vector<CellPosition> const& cellsChecked);

void WriteLabyrinthInFile(std::string const& filePath, Labyrinth const& labyrinth);

void ArgumentsCountCheck(int argc);

bool IsSearchSetting(std::string const& str);

void ValidateArguments(int argc, char* argv[]);

Labyrinth GetLabyrinthFromArgv(int argc, char* argv[]);

SearchSettings GetSearchSetting(int argc, char* argv[]);

Labyrinth GetLabyrinthFromFile(std::string const& filePath, LabyrinthInfo const& labyrinthInfo);

CellPosition GetPositionOf(LabyrinthCells labyrinthCells, Labyrinth const& labyrinth);

std::vector<CellPosition> GetLabeledCellsAround(CellPosition currentCell, Labyrinth& labyrinth, std::vector<CellPosition> const& cellsChecked, bool& labyrinthEndFound);

LabyrinthBorders GetBordersOfLabyrinthFromFile(std::string const& filePath);

LabyrinthInfo GetLabyrinthInfoFromFile(std::string const& filePath);

Labyrinth GetLabyrinthWithShortestPath(Labyrinth const& labyrinthWithoutShortestPath, SearchSettings const& searchSettings);

std::ofstream GetOutputFileStream(std::string const& filePath);

std::ifstream GetInputFileStream(std::string const& filePath);