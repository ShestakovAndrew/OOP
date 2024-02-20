#include <iostream>
#include <fstream>
#include <sstream>
#include <format>
#include <algorithm>
#include <unordered_map>
#include <filesystem>

namespace
{
	enum class RLEMode
	{
		PACK,
		UNPACK
	};

	static std::unordered_map<std::string, RLEMode> const StringToRLEModeTable =
	{
			{"pack", RLEMode::PACK},
			{"unpack", RLEMode::UNPACK}
	};
}

size_t GetFileSize(std::fstream& fileStream)
{
	fileStream.seekg(0, std::ios::end);
	size_t fileSize = fileStream.tellg();
	fileStream.seekg(0, std::ios::beg);
	return fileSize;
}

std::fstream GetFileStream(std::string const& filePath, std::ios::openmode mode)
{
	std::fstream file(filePath, std::ios::binary | mode);
	if (!file.is_open())
	{
		throw std::invalid_argument(
			std::format("Failed to open `{}` file.", filePath)
		);
	}
	return std::move(file);
}

void ValidateArgumentsCounts(int argc)
{
	if (argc != 4)
	{
		throw std::invalid_argument(
			"Usage: rle.exe pack <input file> <output file>\n"
			"Usage: rle.exe unpack <input file> <output file>\n"
			"\t<input file> - path to input file.\n"
			"\t<output file> - path to output file.\n\n"
			"Invalid arguments count."
		);
	}
}

RLEMode GetRLEMode(std::string const& rleModeStr)
{
	auto searchRLEMode = StringToRLEModeTable.find(rleModeStr);

	if (searchRLEMode == StringToRLEModeTable.end())
	{
		throw std::invalid_argument("RLE Mode should be only pack/unpack.");
	}

	return searchRLEMode->second;
}

void PackFile(std::fstream& inputFileStream, std::fstream& outputFileStream)
{
	size_t fileSize = GetFileSize(inputFileStream);
	if (fileSize == 0) return;

	char symbolFirst, symbolSecond;
	uint8_t recurringCount = 1;

	inputFileStream.get(symbolFirst);
	for (size_t symbolInx = recurringCount; symbolInx < fileSize; symbolInx++)
	{
		inputFileStream.get(symbolSecond);
		if (symbolFirst != symbolSecond || recurringCount == 255)
		{
			outputFileStream.put(recurringCount);
			outputFileStream.put(symbolFirst);
			std::swap(symbolFirst, symbolSecond);
			recurringCount = 1;
			continue;
		}
		recurringCount++;
	}
	outputFileStream.put(recurringCount);
	outputFileStream.put(symbolFirst);
}

void UnpackFile(std::fstream& inputFileStream, std::fstream& outputFileStream)
{
	size_t fileSize = GetFileSize(inputFileStream);
	if (fileSize == 0)
	{
		return;
	}

	if (fileSize % 2 != 0)
	{
		throw std::length_error(
			"Unpacking cannot be performed because the file to unpack is not of even length."
		);
	}

	char symbol, countChar;
	uint8_t count = 0;

	for (size_t i = 1; i * 2 <= fileSize; i++)
	{
		inputFileStream.get(countChar);
		inputFileStream.get(symbol);

		count = static_cast<uint8_t>(countChar);
		if (count == 0)
		{
			throw std::range_error(
				"Count of character repetitions should be more zero."
			);
		}

		while (count != 0)
		{
			outputFileStream.put(symbol);
			count--;
		}
	}
}

int main(int argc, char* argv[])
{
	try
	{
		ValidateArgumentsCounts(argc);

		RLEMode rleMode = GetRLEMode(argv[1]);
		std::fstream inputFileStream = GetFileStream(argv[2], std::ios::in);
		std::fstream outputFileStream = GetFileStream(argv[3], std::ios::out);

		if (rleMode == RLEMode::PACK)
		{
			PackFile(inputFileStream, outputFileStream);
			std::cout << "The RLE compression algorithm was successfully applied to the file.";
		}
		else
		{
			UnpackFile(inputFileStream, outputFileStream);
			std::cout << "The RLE algorithm was successfully applied to the file for decompression.";
		}
	}
	catch (std::logic_error const& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}

	return 0;
}