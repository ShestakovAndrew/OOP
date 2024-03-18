#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>

int Validat
	}

	std::string byteStr(argv[1]);
	if (std::any_of(byteStr.begin(), byteStr.end(), [](char ch) { return !std::isdigit(ch); }))
	{
		throw std::invalid_argument("Invalid byte argument. Byte should be [0, 255].");
	}

	int byte = std::stoi(byteStr);

	if (byte < 0 || byte > 255)
	{
		throw std::out_of_range("Out of range.");
	}

	return byte;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		int byte = ValidateArgument(argc, argv);

		std::cout << ((byte >> 7) & 1) + ((byte >> 6) & 1) +
					 ((byte >> 5) & 1) + ((byte >> 4) & 1) +
					 ((byte >> 3) & 1) + ((byte >> 2) & 1) +
					 ((byte >> 1) & 1) + (byte & 1);
	}
	catch (std::logic_error const& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}
}