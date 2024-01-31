#include <iostream>
#include <sstream>
#include <functional>
#include <fstream>
#include <Windows.h>

std::fstream GetStreamFile(std::string const& filePath, std::ios_base::openmode openmode)
{
	std::fstream file(filePath, std::ios::binary | openmode);
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open file.");
	}
	return std::move(file);
}

size_t GetFileLength(std::fstream& fileStream)
{
	fileStream.seekg(0, fileStream.end);
	size_t fileLength = fileStream.tellg();
	fileStream.seekg(0, fileStream.beg);
	return fileLength;
}

void ExtractFragmentFromFile(
	std::string const& inputFile,
	std::string const& outputFile,
	std::string const& startPositionStr,
	std::string const& fragmentSizeStr
)
{
	std::fstream inputFileStream = GetStreamFile(inputFile, std::ios::in);
	std::fstream outputFileStream = GetStreamFile(outputFile, std::ios::out);

	size_t startPosition = std::stoull(startPositionStr);
	size_t fragmentSize = std::stoull(fragmentSizeStr);

	size_t inputFileLength = GetFileLength(inputFileStream);

	if (startPosition > inputFileLength)
	{
		throw std::invalid_argument("Incorrect Position.");
	}

	if ((fragmentSize > inputFileLength) || 
		(startPosition + fragmentSize) > inputFileLength)
	{
		throw std::invalid_argument("Incorrect Range.");
	}

	inputFileStream.seekg(startPosition);

	char ch;
	while (fragmentSize != 0)
	{
		inputFileStream.get(ch);
		if (!outputFileStream.put(ch))
		{
			std::cout << "Failed to save data on disk." << std::endl;
		}
		fragmentSize--;
	}

	inputFileStream.close();
	outputFileStream.close();
}

void CheckArguments(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument(
			"Invalid arguments count.\n"
			"Usage: Extract.exe <input file> <output file> <start position> <fragment size>"
		);
	}

	if (std::stoi(argv[3]) < 0)
	{
		throw std::invalid_argument("Incorrect Position.");
	}

	if (std::stoi(argv[4]) < 1)
	{
		throw std::invalid_argument("Incorrect Range.");
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		CheckArguments(argc, argv);

		ExtractFragmentFromFile(
			argv[1] /*input file*/,
			argv[2] /*output file*/,
			argv[3] /*start position*/,
			argv[4] /*fragment size*/
		);

		std::cout << "Extract successfully." << std::endl;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}