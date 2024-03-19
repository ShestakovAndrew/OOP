#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

const size_t MAX_LIVESTATE_SIZE = 256;

enum class LiveCells
{
	DEAD = -1,
	WALL,
	LIVE
};

static std::unordered_map<char, LiveCells> const LIVE_CELLS_TABLE = {
	{'*', LiveCells::WALL},
	{'#', LiveCells::LIVE},
	{' ', LiveCells::DEAD},
};

static std::unordered_map<LiveCells, char> const INVERT_LIVE_CELLS_TABLE = {
	{LiveCells::WALL, '*'},
	{LiveCells::LIVE, '#'},
	{LiveCells::DEAD, ' '},
};

using NeighborCoordsVector = std::vector<std::pair<size_t, size_t>>;
using LiveVector = std::vector<LiveCells>;
using LiveMatrix = std::vector<LiveVector>;

LiveMatrix GetLiveStateFromFile(std::ifstream& inputFileStream);

NeighborCoordsVector GetNeighborCells(LiveMatrix const& prevLifeState, size_t x, size_t y);

size_t CountLiveNeighbors(LiveMatrix const& prevLifeState, size_t x, size_t y);

LiveMatrix GenerateNextLiveState(LiveMatrix const& prevLifeState);

std::ostream& operator<<(std::ostream& os, LiveMatrix const& lifeState);

void ValidateLiveState(LiveMatrix const& liveState);

bool LiveStateHasCorrectSize(LiveMatrix const& liveState);

bool LiveStateHasFieldBoundaries(LiveMatrix const& liveState);

