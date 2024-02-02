#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

bool isSymbolDecimal(char ch)
{
	return std::isdigit(ch);
}

std::uint32_t ValidateArgument(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument(
			"Usage: dec2bin.exe <number in decimal system>\n"
			"\t<number in decimal system>: 0-4294967295\n\n"
			"Invalid arguments count."
		);
	}

	std::string numberStr(argv[1]);
	if (!std::all_of(numberStr.begin(), numberStr.end(), isSymbolDecimal))
	{
		throw std::invalid_argument(
			"<number in decimal system> should be contain only 0-9."
		);
	}

	return static_cast<uint32_t>(std::stoul(numberStr));
}

std::string Dec2Bin(uint32_t number)
{
	if (number == 0) return "0";

	std::string result;

	while (number) 
	{
		result += (number & 1) ? '1' : '0';
		number >>= 1;   
	}

	std::reverse(result.begin(), result.end());
	return result;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		std::uint32_t number = ValidateArgument(argc, argv);
		std::cout << Dec2Bin(number);
	}
	catch (std::invalid_argument const& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}
	catch (std::out_of_range)
	{
		std::cout << "<number in decimal system> should be in range 0-4294967295." << std::endl;
		return 1;
	}
}