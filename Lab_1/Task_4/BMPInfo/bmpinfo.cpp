#include <iostream>
#include <fstream>
#include <sstream>
#include <format>
#include <algorithm>
#include <unordered_map>

#include "BmpFileHeader.h"

namespace
{
	static const std::unordered_map<BMPCompression, std::string> COMPRESSION_TABLE =
	{
			{BMPCompression::RGB, "RGB"},
			{BMPCompression::RLE_8, "RLE 8"},
			{BMPCompression::RLE_4, "RLE 4"},
			{BMPCompression::BIT_FIELDS, "#Bit Fields"},
			{BMPCompression::JPEG, "JPEG"},
			{BMPCompression::PNG, "PNG"},
			{BMPCompression::ALPHA_BIT_FIELDS, "Alpha Bit Fields"},
	};
}

void ValidateArgumentsCounts(int argc)
{
	if (argc != 2)
	{
		throw std::invalid_argument(
			"Usage: bmpinfo.exe <input file name>\n"
			"\t<input file name> - path to bmp file.\n\n"
			"Invalid arguments count."
		);
	}
}

void PrintBMPInfo(BMPInfo const& bmpInfo)
{
	auto& bmpIH = bmpInfo.bmpInfoHeader;

	std::cout << std::format("Screen Resolution: {}x{}.", bmpIH.width, bmpIH.height) << std::endl;
	std::cout << std::format("Image size (bytes): {}.", bmpIH.sizeImage) << std::endl;
	std::cout << std::format("Bits per pixel: {}.", bmpIH.bitCount) << std::endl;

	if (bmpIH.bitCount <= 8)
	{
		std::cout << std::format("This file uses {} colors.",
			std::pow(2, bmpIH.bitCount)) << std::endl;
	}

	std::cout << std::format("This BMP file uses {} compression method.", 
		COMPRESSION_TABLE.at(bmpIH.compression)) << std::endl;
}

BMPInfo ParseBMPFile(std::ifstream& bmpFile)
{
	BMPInfo bmpInfo{};

	if (!bmpFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(bmpInfo)))
	{
		throw std::length_error("Error reading the beginning of the BMP file.");
	}

	auto& bmpFH = bmpInfo.bmpFileHeader;

	if (std::find(AVAILABLE_BMP_SIGNATURE.begin(), AVAILABLE_BMP_SIGNATURE.end(),
		bmpFH.type) == AVAILABLE_BMP_SIGNATURE.end()
	)
	{
		throw std::length_error("Signature does not comply with the BMP specification.");
	}

	if (bmpFH.fileSize <= 0)
	{
		throw std::length_error("File size cannot be negative or empty.");
	}

	if (bmpFH.reserved != 0)
	{
		throw std::length_error("The size of the reserved area must be zero.");
	}

	auto& bmpIH = bmpInfo.bmpInfoHeader;

	if (bmpIH.sizeInfoHeader != sizeof(BitmapV5Header) &&
		bmpIH.sizeInfoHeader != sizeof(BitmapV4Header) &&
		bmpIH.sizeInfoHeader != sizeof(BitmapInfoHeader)
	)
	{
		throw std::length_error("The header does not fit the size of any version.");
	}

	if (bmpIH.width == 0 || bmpIH.height == 0)
	{
		throw std::length_error("Neither the width nor height of a BMP image can be zero.");
	}

	if (std::find(AVAILABLE_IMAGE_BITS.begin(), AVAILABLE_IMAGE_BITS.end(), 
		bmpIH.bitCount) == AVAILABLE_IMAGE_BITS.end()
	)
	{
		throw std::length_error("Incorrect image bit count.");
	}

	if (bmpIH.sizeImage <= 0)
	{
		throw std::length_error("Image size cannot be negative or empty.");
	}

	if (bmpIH.compression < BMPCompression::RGB || 
		bmpIH.compression > BMPCompression::ALPHA_BIT_FIELDS)
	{
		throw std::length_error("Incorrect image compression.");
	}

	return bmpInfo;
}

std::ifstream GetFileStream(std::string const& filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		throw std::invalid_argument(
			std::format("Failed to open `{}` matrix file.", filePath)
		);
	}
	return std::move(file);
}

int main(int argc, char* argv[])
{
	try
	{
		ValidateArgumentsCounts(argc);

		std::ifstream bmpFileStream = GetFileStream(argv[1]);

		BMPInfo bitmapInfo = ParseBMPFile(bmpFileStream);
		PrintBMPInfo(bitmapInfo);
	}
	catch (std::logic_error const& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}

	return 0;
}