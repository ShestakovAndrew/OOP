#include <iostream>
#include <windows.h>
#include <string>
#include <map>

namespace
{
	struct Value
	{
		bool isNegative = false;
		bool isFloat = false;
		std::string value = "";
	};

	struct Data
	{
		uint16_t sourceNotation = 0;
		uint16_t destinationNotation = 0;
		Value valueInfo;
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

void Converting10BaseToAnyBase(Data& data)
{
	size_t index = 0;
	int64_t decimalNumber = stoll(data.valueInfo.value);
	std::string result;

	while (decimalNumber > 0)
	{
		result.push_back(NumberToSymbol(decimalNumber % data.destinationNotation));
		decimalNumber /= data.destinationNotation;
	}

	reverse(result.begin(), result.end());
	data.valueInfo.value = result;
}
void ConvertingAnyBaseTo10Base(Data& data)
{
	size_t amountNumbers = data.valueInfo.value.size();
	uint64_t powerOfBase = 1;
	int64_t decimalNumber = 0;

	for (size_t i = amountNumbers - 1; i != std::string::npos; i--)
	{
		if (SymbolToNumber(data.valueInfo.value[i]) >= data.sourceNotation)
		{
			throw std::out_of_range("Invalid convert to 10 base.");
		}

		decimalNumber += SymbolToNumber(data.valueInfo.value[i]) * powerOfBase;
		powerOfBase = powerOfBase * data.sourceNotation;
	}

	data.sourceNotation = 10;
	data.valueInfo.value = std::to_string(decimalNumber);
}
void OutputData(Data& data)
{
	if (data.valueInfo.isNegative) std::cout << "-";
	std::cout << data.valueInfo.value << std::endl;
}
void ConvertingRadixs(Data& data)
{
	if (data.sourceNotation != 10 and data.destinationNotation != 10)
	{
		ConvertingAnyBaseTo10Base(data);
		Converting10BaseToAnyBase(data);
	}
	else if (data.destinationNotation == 10)
	{
		ConvertingAnyBaseTo10Base(data);
	}
	else if (data.sourceNotation == 10)
	{
		Converting10BaseToAnyBase(data);
	}
}
Data getDataFromArguments(char* argv[])
{
	Data result; 

	result.sourceNotation = static_cast<uint16_t>(std::stoi(argv[1])); 
	result.destinationNotation = static_cast<uint16_t>(std::stoi(argv[2]));
	result.valueInfo.value = argv[3];

	if (result.valueInfo.value.find("-") != std::string::npos)
	{
		result.valueInfo.value.erase(0, 1);
		result.valueInfo.isNegative = true;
	}

	return result;
}
void ValidateData(Data& data)
{
	if ((data.destinationNotation < 2 or data.destinationNotation > 35) or
		(data.sourceNotation < 2 or data.sourceNotation > 35))
	{
		throw std::out_of_range("Invalid base number.");
	}
}
void CheckArguments(int argc)
{
	if (argc != 4)
	{
		std::cout << "Invalid arguments count." << std::endl
			<< "\tUsage: findtext.exe <source notation> <destination notation> <value>" << std::endl
			<< "\t\t<source notation> - current number system." << std::endl
			<< "\t\t<destination notation> - required number system." << std::endl
			<< "\t\t<value> - number/string to translate." << std::endl;
		throw std::invalid_argument("Invalid arguments count.");
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		CheckArguments(argc);
		Data data = getDataFromArguments(argv);
		ValidateData(data);
		ConvertingRadixs(data);
		OutputData(data);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}