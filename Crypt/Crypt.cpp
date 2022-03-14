#include <iostream>	
#include <string>
#include <fstream>
#include <functional>
#include <windows.h>

namespace
{
	using CryptInstruction = std::function<char(char symbol, uint8_t key)>;

	struct CryptData
	{
		uint8_t key = 0;
		std::ifstream inputFile;
		std::ofstream outputFile;
	};
}

void ArgumentsCountCheck(int argc)
{
	if (argc != 5)
	{
		std::cout << "Usage: crypt.exe <crept/decrypt> <input file> <output file> <key>" << std::endl
			<< "\t<crypt/decrypt> - mode  " << std::endl
			<< "\t<input file> - path to input file." << std::endl
			<< "\t<output file> - path to output file." << std::endl
			<< "\t<key> - integer number in range 0-255." << std::endl;

		throw std::invalid_argument("Invalid arguments count.");
	}
}

std::ifstream GetOpenFileForRead(std::string const& filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open file for read.");
	}

	return move(file);
}

std::ofstream GetOpenFileForWrite(std::string const& filePath)
{
	std::ofstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open file for write.");
	}

	return move(file);
}

CryptData ValidateArguments(int argc, char* argv[])
{
	ArgumentsCountCheck(argc);

	CryptData cryptData;

	cryptData.inputFile = GetOpenFileForRead(argv[2]);
	cryptData.outputFile = GetOpenFileForWrite(argv[3]);
	cryptData.key = std::stoi(argv[4]);

	if (cryptData.key < 0 or cryptData.key > 255)
	{
		throw std::invalid_argument("Key out of range. Key must be 0 - 255.");
	}

	return cryptData;
}

void CryptText(
	CryptData& cryptData,
	CryptInstruction const& instructionToCrypt = CryptInstruction())
{
	char symbol;

	while (cryptData.inputFile.read(&symbol,1))
	{
		if (instructionToCrypt)
		{
			cryptData.outputFile.put(instructionToCrypt(symbol, cryptData.key));
		}
	}
}

char MixingBitsInByte(char symbol)
{
	return ((symbol << 2) & 0b00011100) |
		   ((symbol << 3) & 0b11000000) |
		   ((symbol >> 5) & 0b00000011) |
		   ((symbol >> 2) & 0b00100000);
}

char InvertMixingBitsInByte(char symbol)
{
	return ((symbol >> 2) & 0b00000111) |
		   ((symbol >> 3) & 0b00011000) |
		   ((symbol << 5) & 0b01100000) |
		   ((symbol << 2) & 0b10000000);
}

char CryptSymbol(char symbol, uint8_t key)
{
	return MixingBitsInByte(symbol ^ key);
}

char DecryptSymbol(char symbol, uint8_t key)
{
	return InvertMixingBitsInByte(symbol) ^ key;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		CryptData cryptData = ValidateArguments(argc, argv);

		(argv[1] == "crypt") ? CryptText(cryptData, CryptSymbol) 
			: CryptText(cryptData, DecryptSymbol);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
	}
}