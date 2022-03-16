#include <iostream>
#include <windows.h>
#include <string>

namespace
{
	struct Data
	{
		uint16_t sourceNotation = 0;
		uint16_t destinationNotation = 0;
		std::string value;
	};
}

uint16_t SymbolToNumber(char symbol)
{
	if (symbol >= '0' && symbol <= '9') return (uint16_t)symbol - '0';
	else return (uint16_t)symbol - 'A' + 10;
}

char NumberToSymbol(uint16_t number)
{
	if (number >= 0 && number <= 9)	return (char)(number + '0');
	else return (char)(number - 10 + 'A');
}

std::string ConvertingFromDecimalToAnyNumberSystem(int64_t numderDecimal, uint16_t destinationNotation)
{
	std::string result;

	bool isNegative = (numderDecimal < 0) ? true : false;

	if (isNegative) numderDecimal *= -1;

	while (numderDecimal > 0)
	{
		result.push_back(NumberToSymbol(numderDecimal % destinationNotation));
		numderDecimal /= destinationNotation;
	}

	reverse(result.begin(), result.end());

	return isNegative ? ("-" + result) : result;
}

int64_t ConvertingToDecimalNotation(std::string const& value, uint16_t sourceNotation)
{
	bool isNegative = (value[0] == '-') ? true : false;

	size_t amountNumbers = value.size() - 1;
	uint64_t powerOfBase = 1;
	int64_t decimalNumber = 0;

	for (size_t i = amountNumbers; i != std::string::npos; i--)
	{
		if (value[i] == '-') break;

		decimalNumber += SymbolToNumber(value[i]) * powerOfBase;
		powerOfBase = powerOfBase * sourceNotation;
	}

	return isNegative ? (-1 * decimalNumber) : decimalNumber;
}

std::string Converting(std::string const& value, uint16_t destinationNotation, uint16_t sourceNotation)
{
	if (sourceNotation == destinationNotation or value == "0") return value;

	int64_t numderDecimal = ConvertingToDecimalNotation(value, sourceNotation);
	return ConvertingFromDecimalToAnyNumberSystem(numderDecimal, destinationNotation);
}

void ValidateData(Data const& data)
{
	if ((data.destinationNotation < 2 or data.destinationNotation > 35) or
		(data.sourceNotation < 2 or data.sourceNotation > 35))
	{
		throw std::invalid_argument("Invalid base in arguments.");
	}

	for (const char symbol : data.value)
	{
		if (symbol == '-') continue;

		if (SymbolToNumber(symbol) >= data.sourceNotation)
		{
			throw std::out_of_range("Invalid base of value.");
		}
	}
}

void CheckArguments(int argc)
{
	if (argc != 4)
	{
		std::cout << "Usage: findtext.exe <source notation> <destination notation> <value>" << std::endl
			<< "\t<source notation> - current number system (2 - 35)." << std::endl
			<< "\t<destination notation> - required number system (2 - 35)." << std::endl
			<< "\t<value> - number to translate." << std::endl;
		throw std::invalid_argument("Invalid arguments count.");
	}
}

Data getDataFromArguments(int argc, char* argv[])
{
	CheckArguments(argc);
	Data result;

	result.sourceNotation = static_cast<uint16_t>(std::stoi(argv[1]));
	result.destinationNotation = static_cast<uint16_t>(std::stoi(argv[2]));
	result.value = argv[3];

	ValidateData(result);

	return result;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		Data data = getDataFromArguments(argc, argv);
		std::cout << Converting(data.value, data.destinationNotation, data.sourceNotation) << std::endl;
	}
	catch (std::logic_error const& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}