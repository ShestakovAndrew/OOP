#include <iostream>
#include <windows.h>
#include <string>

void CheckArguments(int argc)
{
	if (argc != 2)
	{
		throw std::invalid_argument(
			"Usage: calcbits.exe <byte>\n"
			"\t<byte> - [0,255]\n\n"
			"Invalid arguments count."
		);
	}
}

int CheckByteRange(std::string const& byteStr)
{
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
		CheckArguments(argc);

		int byte = CheckByteRange(argv[1]);

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