#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

bool ValidateRange(std::string const& str, uint8_t min, uint8_t max)
{
	return 
		std::any_of(str.begin(), str.end(), [](char ch) { return !std::isdigit(ch); }) ||
		std::stoi(str) < min || std::stoi(str) > max;
}

void ValidateArgument(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::invalid_argument(
			"Usage: rotatebyte.exe <byte> <number of bits> <L / R>\n"
			"\t<byte> - [0,255]\n"
			"\t<number of bits> - [0,8]\n"
			"\t<L / R> - L or R\n\n"
			"Invalid arguments count."
		);
	}

	std::string byteStr(argv[1]);
	if (ValidateRange(byteStr, 0, 255))
	{
		throw std::invalid_argument("<byte> should be in [0, 255].");
	}

	std::string numBitsStr(argv[2]);
	if (ValidateRange(numBitsStr, 0, 8))
	{
		throw std::invalid_argument("<number of bit> should be in [0, 8].");
	}

	char sideRotate = argv[3][0];
	if ((sideRotate != 'R') && (sideRotate != 'L'))
	{
		throw std::invalid_argument("<L / R> should be only L or R letter.");
	}
}

uint8_t LeftRotate(uint8_t byte, uint8_t numBits)
{
	return (byte << numBits) | (byte >> (8 - numBits));
}

uint8_t RightRotate(uint8_t byte, uint8_t numBits)
{
	return (byte >> numBits) | (byte << (8 - numBits));
}

int RotateByte(uint8_t byte, uint8_t numBits, char sideRotate)
{
	if (numBits == 0 || numBits == 8)
	{
		return byte;
	}

	bool isLeftRotate = (sideRotate == 'L');

	return isLeftRotate ? LeftRotate(byte, numBits) : RightRotate(byte, numBits);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		ValidateArgument(argc, argv);

		std::cout << RotateByte(
			std::stoi(argv[1]) /*byte*/,
			std::stoi(argv[2]) /*number of bits*/,
			argv[3][0] /*side rotate*/
		);
	}
	catch (std::invalid_argument const& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}
}