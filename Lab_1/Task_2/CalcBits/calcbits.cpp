#include <iostream>
#include <windows.h>
#include <string>

void CheckArguments(int argc)
{
	if (argc != 1)
	{
		throw std::invalid_argument(
			"Usage: calcbits.exe <byte>\n"
			"\t<byte> - [0,255]\n\n"
			"Invalid arguments count."
		);
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		CheckArguments(argc);

	}
	catch (std::invalid_argument const& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}