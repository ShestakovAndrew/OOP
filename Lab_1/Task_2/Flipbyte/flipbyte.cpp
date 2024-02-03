#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

bool isSymbolDecimal(char ch)
{
	return std::isdigit(ch);
}

std::uint8_t ValidateArgument(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument(
			"Usage: flipbyte.exe <input byte>\n"
			"\t<input byte>: 0-255\n\n"
			"Invalid arguments count."
		);
	}

	std::string numberStr(argv[1]);
	if (!std::all_of(numberStr.begin(), numberStr.end(), isSymbolDecimal))
	{
		throw std::invalid_argument(
			"<input byte> should be contain only 0-9 digits."
		);
	}

	int inputByte = std::stoi(numberStr);
	if (inputByte < 0 || inputByte > 255)
	{
		throw std::invalid_argument(
			"<input byte> should be in range 0-255."
		);
	}

	return static_cast<uint8_t>(inputByte);
}

uint8_t FlipByte(uint8_t inputByte)
{
	if (inputByte == 0) return 0;
	if (inputByte == 255) return 255;

	return ((inputByte << 7) & 128) |
		   ((inputByte << 5) & 64)  |
		   ((inputByte << 3) & 32)  |
		   ((inputByte << 1) & 16)  | 
		   ((inputByte >> 1) & 8)   |
		   ((inputByte >> 3) & 4)   |
		   ((inputByte >> 5) & 2)   | 
		   ((inputByte >> 7) & 1);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		std::uint8_t inputByte = ValidateArgument(argc, argv);
		std::cout << +FlipByte(inputByte);
	}
	catch (std::invalid_argument const& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}
}