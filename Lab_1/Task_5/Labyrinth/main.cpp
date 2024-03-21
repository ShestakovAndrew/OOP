#include <format>

#include "Labyrinth.h"

std::ifstream GetInputFileStream(std::string const& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		throw std::invalid_argument(
			std::format("Failed to open `{}` file for read.", filePath)
		);
	}
	return std::move(file);
}

std::ofstream GetOutputFileStream(std::string const& filePath)
{
	std::ofstream file(filePath);
	if (!file.is_open())
	{
		throw std::invalid_argument(
			std::format("Failed to open `{}` file for write.", filePath)
		);
	}
	return std::move(file);
}

void ValidateArgumentsCount(int argc)
{
	if (argc != 3)
	{
		throw std::invalid_argument(
			"Usage: labyrinth.exe <input file> <output file> <setting for search>\n"
			"\t<input file> - path to input file.\n"
			"\t<output file> - path to output file.\n"
			"Invalid arguments count."
		);
	}
}

int main(int argc, char* argv[])
{
	try
	{
		ValidateArgumentsCount(argc);

		std::ifstream inputFileStream = GetInputFileStream(argv[1]);
		std::ofstream outputFileStream = GetOutputFileStream(argv[2]);

		LabyrinthMatrix labyrinth = GetLabyrinthFromStream(inputFileStream);

		ValidateLabyrinth(labyrinth);

		outputFileStream << GetLabyrinthWithShortestPath(labyrinth);

		std::cout << "Path in labyrinth was successfully founded." << std::endl;
	}
	catch (std::exception const& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}