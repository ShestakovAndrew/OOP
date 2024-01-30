#include <iostream>
#include <sstream>
#include <functional>
#include <fstream>
#include <Windows.h>

std::fstream GetStreamFile(std::string const& filePath, std::ios_base::openmode mode)
{
	std::fstream file(filePath, mode, std::ios::binary);
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open file.");
	}
	return std::move(file);
}

void CheckArguments(int argc)
{
	if (argc < 3)
	{
		std::cout << "Usage: join.exe <input file1> ... <input file N> <output file>" << std::endl;
		throw std::invalid_argument("Invalid arguments count.");
	}
}

bool JoinFiles(int argc, char* argv[])
{
	size_t indexOutputFile = argc - 1;
	std::fstream outputFileStream = GetStreamFile(argv[indexOutputFile], std::ios::out);

	bool isFileJoined = false;

	for (size_t inputFileIndex = 1; inputFileIndex < indexOutputFile; inputFileIndex++)
	{
		std::fstream inputFileStream = GetStreamFile(argv[inputFileIndex], std::ios::in);
		std::string line;

		for (size_t lineIndex = 1; std::getline(inputFileStream, line); lineIndex++)
		{
			isFileJoined = true;
			outputFileStream << line << std::endl;
		}

		inputFileStream.close();
	}

	outputFileStream.close();
	return isFileJoined;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		CheckArguments(argc);
		if (!JoinFiles(argc, argv))
		{
			std::cout << "Nothing to join." << std::endl;
			return 1;
		}

		std::cout << "Join successfully." << std::endl;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}