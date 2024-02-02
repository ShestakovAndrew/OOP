#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

bool isSymbolOneOrZero(char ch)
{
	return !(ch == '1' || ch == '0');
}

void ValidateArgument(int argc)
{
	if (argc != 2)
	{
		throw std::invalid_argument(
			"Usage: bin2dec.exe <number in binary system>\n"
			"\t<number in binary system>: 0-32 bits\n\n"
			"Invalid arguments count."
		);
	}
}

uint32_t Bin2Dec(std::string const& binStr)
{
	size_t length = binStr.length();

	if (std::all_of(binStr.begin(), binStr.end(), isSymbolOneOrZero) ||
		length < 0 || length > 32)
	{
		throw std::invalid_argument("<number in binary system> should be 0-32 bits.");
	}

	uint32_t result = 0;
	size_t offset = 1;

	for (size_t bitPos = 0; bitPos <= binStr.length(); bitPos++, offset++)
	{
		if (binStr[bitPos] == '1')
		{
			result |= (1 << (length - offset));
		}
	}

	return result;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		ValidateArgument(argc);

		std::cout << Bin2Dec(argv[1] /*number in binary*/);
	}
	catch (std::invalid_argument const& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}
}