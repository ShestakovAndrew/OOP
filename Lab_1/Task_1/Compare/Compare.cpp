#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* const argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count" << std::endl
			<< "Usage: compare.exe <file1> <file2>" << std::endl;
		return 1;
	}

	std::ifstream file1(argv[1], std::ifstream::binary);
	if (!file1.is_open())
	{
		std::cout << "Failed to open " << argv[1] << std::endl;
		return 1;
	}

	std::ifstream file2(argv[2], std::ifstream::binary);
	if (!file2.is_open())
	{
		std::cout << "Failed to open " << argv[2] << std::endl;
		return 1;
	}

	if (file1.tellg() != file2.tellg()) 
	{
		std::cout << "Files of different sizes" << std::endl;
		return 1; 
	}

	std::string lineFromFirstFile;
	std::string lineFromSecondFile;
	size_t lineCounter = 0;

	while (!file1.eof() || !file2.eof())
	{
		std::getline(file1, lineFromFirstFile);
		std::getline(file2, lineFromSecondFile);
		lineCounter++;

		if (lineFromFirstFile != lineFromSecondFile)
		{
			std::cout << "Files are different. Line number is " << lineCounter << std::endl;
			return 1;
		}
	}

	std::cout << "Files are equal" << std::endl;
	return 0;
}