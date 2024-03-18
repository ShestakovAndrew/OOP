#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <array>
#include <unordered_map>

namespace
{
	const size_t MAX_LIVESTATE_SIZE = 256;
	using LiveVector = std::vector<LiveCells>;
	using LiveState = std::vector<LiveVector>;

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
}

void ValidateArgumentsCount(int argc)
{
	if (argc < 2 || argc > 3)
	{
		throw std::invalid_argument(
			"Usage: Life.exe <input file> [<output file>]\n"
			"\t<input file> - path to input file.\n"
			"\t[<output file>] - optional path to output file.\n\n"
			"Invalid arguments count."
		);
	}
}

std::ifstream GetInputFileStream(std::string const& filePath, std::ios::openmode mode)
{
	std::ifstream file(filePath, mode);
	if (!file.is_open())
	{
		throw std::invalid_argument(
			std::format("Failed to open `{}` file for read.", filePath)
		);
	}
	return std::move(file);
}

std::ofstream GetOutputFileStream(std::string const& filePath, std::ios::openmode mode)
{
	std::ofstream file(filePath, mode);
	if (!file.is_open())
	{
		throw std::invalid_argument(
			std::format("Failed to open `{}` file for write.", filePath)
		);
	}
	return std::move(file);
}

LiveState GetLiveStateFromFile(std::ifstream& inputFileStream)
{
	LiveState liveState;
	std::string fileLine;

	while (std::getline(inputFileStream, fileLine))
	{
		LiveVector liveLine;
		for (char const& cell : fileLine)
		{
			liveLine.push_back(LIVE_CELLS_TABLE.find(cell)->second);
		}
		liveState.push_back(liveLine);
	}

	return liveState;
}

LiveState GetNextLiveState(LiveState const& lifeState)
{
	LiveState nextLifeState(lifeState);



	return nextLifeState;
}

std::ostream& operator<<(std::ostream& os, LiveState const& lifeState)
{
}

int main(int argc, char* argv[])
{
	try
	{
		ValidateArgumentsCount(argc);
		std::ifstream inputFileStream = GetInputFileStream(argv[1], std::ios::in);
		
		std::ostream& outputStream = (argc == 3) 
			? static_cast<std::ostream&>(GetOutputFileStream(argv[2], std::ios::out)) 
			: std::cout;

		LiveState liveState = GetLiveStateFromFile(inputFileStream);
		outputStream << GetNextLiveState(liveState);
	}
	catch (std::exception const& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}