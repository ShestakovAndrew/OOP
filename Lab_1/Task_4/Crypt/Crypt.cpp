#include <iostream>	
#include <string>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <format>
#include <algorithm>

namespace
{
	using CryptFunction = std::function<char(char symbolToCrypt, uint8_t key)>;

	enum class CryptionMethod
	{
		ENCRYPT,
		DECRYPT
	};

	static std::unordered_map<std::string, CryptionMethod> const cryptionMethodTable = {
			{"encrypt", CryptionMethod::ENCRYPT}, 
			{"decrypt", CryptionMethod::DECRYPT} 
	};
}

bool isSymbolDecimal(char ch)
{
	return std::isdigit(ch);
}

void ValidateArgumentsCount(int argc)
{
	if (argc != 5)
	{
		throw std::invalid_argument(
			"Usage: crypt.exe <encrept/decrypt> <input file> <output file> <key>\n"
			"\t<encrypt/decrypt> - mode to crypt symbols in text.\n"
			"\t<input file> - path to input file.\n"
			"\t<output file> - path to output file.\n"
			"\t<key> - integer number in range 0-255.\n\n"
			"Invalid arguments count."
		);
	}
}

CryptionMethod GetCryptionMethod(std::string const& str)
{
	if (cryptionMethodTable.find(str) == cryptionMethodTable.end())
	{
		throw std::invalid_argument("Encryption/decryption instruction failed set.");
	}
	return cryptionMethodTable.find(str)->second;
}

uint8_t GetKey(std::string const& str)
{
	if (!std::all_of(str.begin(), str.end(), isSymbolDecimal))
	{
		throw std::invalid_argument("Key should be integer (0 - 255).");
	}

	uint8_t key = std::stoi(str);
	if (!std::all_of(str.begin(), str.end(), isSymbolDecimal) || key < 0 || key > 255)
	{
		throw std::out_of_range("Key out of range. Key must be 0 - 255.");
	}
	return key;
}

std::ifstream GetFileStreamForRead(std::string const& filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		throw std::invalid_argument(
			std::format("Failed to open `{}` file for read..", filePath)
		);
	}
	return std::move(file);
}

std::ofstream GetFileStreamForWrite(std::string const& filePath)
{
	std::ofstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		throw std::invalid_argument(
			std::format("Failed to open `{}` file for write.", filePath)
		);
	}
	return std::move(file);
}

void CryptText(
	std::ifstream& inputFile, 
	std::ofstream& outputFile, 
	uint8_t key,
	CryptFunction const& cryptSymbol
)
{
	char symbol;
	while (inputFile.read(&symbol, 1))
	{
		outputFile.put(cryptSymbol(symbol, key));
	}
}

char MixingBitsInByte(char symbol)
{
	return ((symbol << 3) & 0b11000000) |
		   ((symbol >> 2) & 0b00100000) |
		   ((symbol << 2) & 0b00011100) |
		   ((symbol >> 5) & 0b00000011);
}

char InvertMixingBitsInByte(char symbol)
{
	return ((symbol >> 2) & 0b00000111) |
		   ((symbol >> 3) & 0b00011000) |
		   ((symbol << 5) & 0b01100000) |
		   ((symbol << 2) & 0b10000000);
}

char EncryptSymbol(char symbol, uint8_t key)
{
	return MixingBitsInByte(symbol ^ key);
}

char DecryptSymbol(char symbol, uint8_t key)
{
	return InvertMixingBitsInByte(symbol) ^ key;
}

int main(int argc, const char* argv[])
{
	try
	{
		ValidateArgumentsCount(argc);

		CryptionMethod cryptionMethod = GetCryptionMethod(argv[1]);
		std::ifstream inputFileStream = GetFileStreamForRead(argv[2]);
		std::ofstream outputFileStream = GetFileStreamForWrite(argv[3]);
		uint8_t key = GetKey(argv[4]);

		if (cryptionMethod == CryptionMethod::ENCRYPT)
		{
			CryptText(inputFileStream, outputFileStream, key, EncryptSymbol);
		}
		else
		{
			CryptText(inputFileStream, outputFileStream, key, DecryptSymbol);
		}
	}
	catch (std::invalid_argument const& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}