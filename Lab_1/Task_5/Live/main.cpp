#include <iostream>
#include <format>

#include "live.h"

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

int main(int argc, char* argv[])
{
	try
	{
		ValidateArgumentsCount(argc);
		std::ifstream inputFileStream = GetInputFileStream(argv[1], std::ios::in);
		
		std::ostream& outputStream = (argc == 3) 
			? (std::ostream&)GetOutputFileStream(argv[2], std::ios::out) 
			: std::cout;

		LiveMatrix liveState = GetLiveStateFromFile(inputFileStream);

		ValidateLiveState(liveState);

		outputStream << GenerateNextLiveState(liveState);
		
		std::cout << "Generate next live state was successfully." << std::endl;
	}
	catch (std::exception const& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}