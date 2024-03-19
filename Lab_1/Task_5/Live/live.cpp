#include "live.h"

bool LiveStateHasFieldBoundaries(LiveMatrix const& liveState)
{
	for (size_t i = 0; i < liveState.size(); i++)
	{
		if (i == 0 || i == liveState.size() - 1)
		{
			for (size_t j = 0; j < liveState[i].size(); j++)
			{
				if (liveState[i][j] != LiveCells::WALL)
				{
					return false;
				}
			}
		}
		else
		{
			if (liveState[i].front() != LiveCells::WALL
				|| liveState[i].back() != LiveCells::WALL)
			{
				return false;
			}
		}
	}

	return true;
}

bool LiveStateHasCorrectSize(LiveMatrix const& liveState)
{
	if (liveState.size() == 0 || liveState.size() > 256)
	{
		return false;
	}

	for (size_t i = 0; i < liveState.size(); i++)
	{
		if (liveState[i].size() > 256)
		{
			return false;
		}
	}

	return true;
}

void ValidateLiveState(LiveMatrix const& liveState)
{
	if (!LiveStateHasCorrectSize(liveState))
	{
		throw std::length_error("Start life state should be max 256x256.");
	}

	if (!LiveStateHasFieldBoundaries(liveState))
	{
		throw std::logic_error("Start life state should be with all wall around.");
	}
}

LiveMatrix GetLiveStateFromFile(std::ifstream& inputFileStream)
{
	LiveMatrix liveState;
	std::string fileLine;

	while (std::getline(inputFileStream, fileLine))
	{
		LiveVector liveLine;
		for (char const& cell : fileLine)
		{
			auto it = LIVE_CELLS_TABLE.find(cell);
			if (it == LIVE_CELLS_TABLE.end())
			{
				throw std::logic_error("Start life state has error symbol.");
			}
			liveLine.push_back(it->second);
		}
		liveState.push_back(liveLine);
	}

	return liveState;
}

NeighborCoordsVector GetNeighborCells(LiveMatrix const& prevLifeState, size_t x, size_t y)
{
	NeighborCoordsVector neighborCoordsVector;

	for (size_t i = x - 1; i <= x + 1; i++)
	{
		for (size_t j = y - 1; j <= y + 1; j++)
		{
			if (i == x && j == y) continue;
			neighborCoordsVector.push_back(std::make_pair(i, j));
		}
	}

	return neighborCoordsVector;
}

size_t CountLiveNeighbors(LiveMatrix const& prevLifeState, size_t x, size_t y)
{
	size_t result = 0;
	NeighborCoordsVector neighborCoordsMatrix = GetNeighborCells(prevLifeState, x, y);
	size_t newX, newY;

	for (size_t i = 0; i < 8; i++)
	{
		newX = neighborCoordsMatrix[i].first;
		newY = neighborCoordsMatrix[i].second;

		if (newX < 0 || newY < 0) continue;

		if (newX >= prevLifeState.size() || newY >= prevLifeState.size()) continue;

		if (prevLifeState[newX][newY] == LiveCells::LIVE) result++;
	}

	return result;
}

LiveMatrix GenerateNextLiveState(LiveMatrix const& prevLifeState)
{
	LiveMatrix nextLifeState(prevLifeState);

	for (size_t x = 0; x < prevLifeState.size(); ++x)
	{
		for (size_t y = 0; y < prevLifeState[x].size(); ++y)
		{
			LiveCells currentCell = prevLifeState[x][y];

			if (currentCell == LiveCells::WALL) continue;

			size_t countLiveCells = CountLiveNeighbors(prevLifeState, x, y);

			if (currentCell == LiveCells::LIVE)
			{
				nextLifeState[x][y] = ((countLiveCells == 2) || (countLiveCells == 3))
					? LiveCells::LIVE
					: LiveCells::DEAD;
				continue;
			}
			else
			{
				if (countLiveCells == 3)
				{
					nextLifeState[x][y] = LiveCells::LIVE;
				}
			}
		}
	}

	return nextLifeState;
}

std::ostream& operator<<(std::ostream& os, LiveMatrix const& lifeState)
{
	for (size_t i = 0; i < lifeState.size(); ++i)
	{
		for (size_t j = 0; j < lifeState[i].size(); ++j)
		{
			os << INVERT_LIVE_CELLS_TABLE.find(lifeState[i][j])->second;
		}
		os << std::endl;
	}

	return os;
}