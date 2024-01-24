#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count" << std::endl
			 << "Usage: copyfile.exe <input file> <output file>" << std::endl;                              
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cout << "Failed to open " << argv[1] << " for reading" << std::endl;              
		return 1;
	}

	std::ofstream output(argv[2]);
	if (!output.is_open())
	{
		std::cout << "Failed to open " << argv[2] << " for writing" << std::endl;
		return 1;
	}

	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			std::cout << "Failed to save data on disk" << std::endl;
			return 1;
		}
	}

	if (!output.flush())
	{
		std::cout << "Failed to save data on disk" << std::endl;
		return 1;
	}

	return 0;
}