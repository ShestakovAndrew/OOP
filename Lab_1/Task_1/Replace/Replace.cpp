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

std::string ReplaceString(
	const std::string& subject, 
	const std::string& searchString, 
	const std::string& replacementString
)
{
	std::string result;

	size_t position = 0; 
	size_t foundPosition = 0;

	while (position < subject.length())
	{
		foundPosition = subject.find(searchString, position);

		if (foundPosition == std::string::npos)
		{
			result.append(subject, position, std::string::npos);
			break;
		}
		else
		{
			result.append(subject, position, foundPosition - position);
			result += replacementString;
			position = foundPosition + searchString.length();
		}
	}

	return result;
}

void CopyFileWithReplacement(
	std::string const& inputFile,
	std::string const& outputFile,
	std::string const& searchString, 
	std::string const& replacementString
)
{
	std::string line;

	std::fstream inputFileStream = GetStreamFile(inputFile, std::ios::in);
	std::fstream outputFileStream = GetStreamFile(outputFile, std::ios::out);

	while (std::getline(inputFileStream, line))
	{
		outputFileStream << ReplaceString(line, searchString, replacementString) << std::endl;
	}

	outputFileStream.flush();
	inputFileStream.close();
}

void CheckArguments(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument(
			"Invalid arguments count.\n"
			"Usage: Replace.exe <input file> <output file> <search string> <replace string>"
		);
	}

	if (std::string(argv[1]) == std::string(argv[2]))
	{
		throw std::invalid_argument("Files identical.");
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		CheckArguments(argc, argv);

		CopyFileWithReplacement(
			argv[1] /*input file*/,
			argv[2] /*output file*/,
			argv[3] /*search string*/,
			argv[4] /*replace string*/
		);

		std::cout << "Replace successfully." << std::endl;
	}
	catch (const std::invalid_argument& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}

	return 0;
}