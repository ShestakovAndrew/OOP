#include <iostream>
#include <fstream>
#include <format>
#include <array>
#include <unordered_map>

namespace
{
	using Matrix = std::array<std::array<char, 256>, 256>;

	enum class LiveCells
	{
		WALL,
		LIVE,
		DEAD
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

std::fstream GetFileStream(std::string const& filePath, std::ios::openmode mode)
{
	std::fstream file(filePath, mode);
	if (!file.is_open())
	{
		throw std::invalid_argument(
			std::format("Failed to open `{}` file.", filePath)
		);
	}
	return std::move(file);
}

int main(int argc, char* argv[])
{
	try
	{
		ValidateArgumentsCount(argc);
		std::fstream inputFileStream = GetFileStream(argv[1], std::ios::in);

		std::fstream outputFileStream;
		if (argc == 3)
		{
			outputFileStream = GetFileStream(argv[2], std::ios::out);
		}
		std::ostream& outputStream = ((argc == 3) ? outputFileStream : std::cout);
	}
	catch (std::exception const& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}