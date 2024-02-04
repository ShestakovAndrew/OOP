#include <iostream>
#include <string>
#include <algorithm>
#include <format>

bool isCharDigit(const char ch)
{
	return std::isdigit(ch);
}

bool isCharAlpha(const char ch)
{
	return std::isalpha(ch);
}

uint8_t CharToDigit(const char symbol)
{
	if (symbol >= '0' && symbol <= '9') return static_cast<uint8_t>(symbol - '0');
	else return static_cast<uint8_t>(symbol - 'A' + 10);
}

char DigitToChar(const uint8_t number)
{
	if (number >= 0 && number <= 9)	return static_cast<char>(number + '0');
	else return static_cast<char>(number - 10 + 'A');
}

bool isValueInRangeNotation(std::string const& value, const uint8_t sourceNotation)
{
	bool isNegativeValue = (value[0] == '-');

	return std::all_of(isNegativeValue ? (value.begin() + 1) : value.begin(), value.end(),
		[&sourceNotation](char ch)
		{
			return CharToDigit(ch) < sourceNotation;
		}
	);
}

std::string ConvertingFromDecimalTo(int64_t numberDecimal, const uint8_t destinationNotation)
{
	std::string result;

	while (numberDecimal > 0)
	{
		result.push_back(DigitToChar(numberDecimal % destinationNotation));
		numberDecimal /= destinationNotation;
	}

	reverse(result.begin(), result.end());

	return result;
}

size_t ConvertingToDecimalFrom(std::string const& value, const uint8_t sourceNotation)
{
	size_t result = 0;
	size_t powerOfBase = 1;

	for (size_t index = value.length() - 1; index != std::string::npos; index--)
	{
		if (value[index] == '-') break;

		result += CharToDigit(value[index]) * powerOfBase;
		powerOfBase *= sourceNotation;
	}

	return result;
}

std::string Radix(
	const uint8_t sourceNotation, 
	const uint8_t destinationNotation, 
	std::string const& value
)
{
	if ((sourceNotation == destinationNotation) || (value == "0")) return value;

	size_t decimalNumber = ConvertingToDecimalFrom(value, sourceNotation);

	bool isNegativeValue = (value[0] == '-');

	return std::format("{}{}", 
		isNegativeValue ? "-" : "", 
		ConvertingFromDecimalTo(decimalNumber, destinationNotation)
	);
}

uint8_t ValidateNotation(std::string const& notationStr, std::string const& nameNotation)
{
	if (!std::all_of(notationStr.begin(), notationStr.end(), isCharDigit))
	{
		throw std::invalid_argument(std::format(
			"<{} notation> should be contain only digits in range [2;36].", nameNotation)
		);
	}

	uint8_t notation = static_cast<uint8_t>(std::stoul(notationStr));

	if (notation < 2 || notation > 36)
	{
		throw std::invalid_argument(std::format(
			"<{} notation> should be in range [2;36].", nameNotation)
		);
	}

	return notation;
}

void ValidateValue(std::string const& value, const uint8_t sourceNotation)
{
	if (!isValueInRangeNotation(value, sourceNotation))
	{
		throw std::invalid_argument(
			"<value> should be contain only digits and alphas in range of <source notation>."
		);
	}
}

void ValidateArgumentsCount(int argc)
{
	if (argc != 4)
	{
		throw std::invalid_argument(
			"Usage: radix.exe <source notation> <destination notation> <value>\n"
			"\t<source notation> - current number system [2;36].\n"
			"\t<destination notation> - required number system [2;36].\n"
			"\t<value> - number to translate.\n\n"
			"Invalid arguments count."
		);
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		ValidateArgumentsCount(argc);

		uint8_t sourceNotation = ValidateNotation(
			argv[1] /*Source Notation*/, "source" /*Notation name*/
		);

		uint8_t destinationNotation = ValidateNotation(
			argv[2] /*Destination Notation*/, "destination" /*Notation name*/
		);

		ValidateValue(argv[3], sourceNotation);

		std::cout << Radix(sourceNotation, destinationNotation, argv[3] /*value*/) << std::endl;
	}
	catch (std::logic_error const& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}
}