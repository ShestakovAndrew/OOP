#include <iostream>	
#include <string>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <windows.h>

namespace
{
	using CryptFunction = std::function<char(char symbolToCrypt, uint8_t key)>;

	enum class CryptionMethod
	{
		ENCRYPT,
		DECRYPT
	};

	static std::unordered_map<std::string, CryptionMethod> const table = { 
			{"encrypt", CryptionMethod::ENCRYPT}, 
			{"decrypt", CryptionMethod::DECRYPT} 
	};

	struct CryptData
	{
		uint8_t key = 0;
		std::ifstream inputFile;
		std::ofstream outputFile;
		CryptionMethod method = CryptionMethod::ENCRYPT;
	};
}

bool IsCryptionMethod(std::string const& str)
{
	return (table.find(str) != table.end()) ? true : false;
}

void ArgumentsCountCheck(int argc)
{
	if (argc != 5)
	{
		std::cout << "Usage: crypt.exe <encrept/decrypt> <input file> <output file> <key>" << std::endl
			<< "\t<encrypt/decrypt> - mode to crypt symbols in text." << std::endl
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

CryptData ValidateArguments(int argc, const char* argv[])
{
	ArgumentsCountCheck(argc);

	if (!IsCryptionMethod(argv[1]))
	{
		throw std::invalid_argument("Encryption/decryption instruction failed set.");
	}

	if (std::stoi(argv[4]) < 0 or std::stoi(argv[4]) > 255)
	{
		throw std::invalid_argument("Key out of range. Key must be 0 - 255.");
	}

	CryptData cryptData;

	cryptData.method = table.find(argv[1])->second;
	cryptData.inputFile = GetOpenFileForRead(argv[2]);
	cryptData.outputFile = GetOpenFileForWrite(argv[3]);
	cryptData.key = std::stoi(argv[4]);

	return cryptData;
}

void CryptText(
	std::ifstream& inputFile,
	std::ofstream& outputFile,
	uint8_t key,
	CryptFunction const& cryptSymbol)
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
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		CryptData cryptData = ValidateArguments(argc, argv);

		if (cryptData.method == CryptionMethod::ENCRYPT)
		{
			CryptText(cryptData.inputFile, cryptData.outputFile, cryptData.key, EncryptSymbol);
		}
		else
		{
			CryptText(cryptData.inputFile, cryptData.outputFile, cryptData.key, DecryptSymbol);
		}
	}
	catch (const std::invalid_argument& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}