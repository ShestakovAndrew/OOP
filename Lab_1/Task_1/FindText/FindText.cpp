#include <iostream>
#include <sstream>
#include <functional>
#include <fstream>
#include <Windows.h>

using FindStringCallback = std::function<void(
	size_t lineIndex, 
	std::string const& line, 
	size_t foundPos
)>;

std::ifstream GetStreamFromFile(std::string const& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open file.");
	}
	return std::move(file);
}

bool FindStringInFile(
	std::string const& filePath,
	std::string const& needle,
	FindStringCallback const& notification = FindStringCallback())
{
	std::ifstream fileStream = GetStreamFromFile(filePath);
	std::string line;
	bool found = false;

	for (size_t lineIndex = 1; std::getline(fileStream, line); lineIndex++)
	{
		size_t pos = line.find(needle);
		while (pos != std::string::npos)
		{
			found = true;
			notification(lineIndex, line, pos);
			pos = line.find(needle, pos + 1);
		}
	}

	return found;
} 

void PrintFoundLineIndex(size_t lineIndex, std::string const& line, size_t foundPos)
{
	std::cout << 
		"lineIndex: " << lineIndex << "; " << 
		"foundPos: " << foundPos << "; " << 
		"line: " << line << std::endl;
}

void CheckArguments(int argc)
{
	if (argc != 3)
	{
		std::cout << "Usage: findtext.exe <file name> <text to search>" << std::endl;
		throw std::invalid_argument("Invalid arguments count.");
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		CheckArguments(argc);
		if (!FindStringInFile(argv[1] /*file*/, argv[2] /*NeedToFind*/, PrintFoundLineIndex))
		{
			std::cout << "Text not found." << std::endl;
			return 1;
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}