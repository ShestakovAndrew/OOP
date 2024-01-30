#include <iostream>
#include <sstream>
#include <functional>
#include <fstream>
#include <Windows.h>

std::fstream GetStreamFile(std::string const& filePath, std::ios_base::openmode mode)
{
	std::fstream file(filePath, mode);
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open file.");
	}
	return std::move(file);
}

bool ReplaceStringsInFile(
	std::string const& inputFile,
	std::string const& outputFile,
	std::string const& wordToReplace,
	std::string const& wordReplace
	)
{
	std::fstream inputFileStream = GetStreamFile(inputFile, std::ios::in);
	std::fstream outputFileStream = GetStreamFile(outputFile, std::ios::out);

	size_t wordToReplaceLength = wordToReplace.length();
	size_t wordReplaceLength = wordReplace.length();

	std::string line;
	bool isReplaced = false;

	for (size_t lineIndex = 1; std::getline(inputFileStream, line); lineIndex++)
	{
		size_t position{};
		while ((position = line.find(wordToReplace, position)) != std::string::npos)
		{
			isReplaced = true;
			line.replace(position, wordToReplaceLength, wordReplace);
			position += wordReplaceLength;
		}
		outputFileStream << line << std::endl;
	}

	inputFileStream.close();
	outputFileStream.close();

	return isReplaced;
}

void CheckArguments(int argc)
{
	if (argc != 5)
	{
		std::cout << "Replace.exe <input file> <output file> <search string> <replace string>"
			<< std::endl;

		throw std::invalid_argument("Invalid arguments count.");
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		CheckArguments(argc);
		if (!ReplaceStringsInFile(argv[1] /*input file*/,    argv[2] /*output file*/,
								  argv[3] /*search string*/, argv[4] /*replace string*/)
		) 
		{
			std::cout << "No matches found to replace." << std::endl;
			return 1;
		}
		else
		{
			std::cout << "Replace successfully." << std::endl;
		}

	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}