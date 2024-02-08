#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <format>
#include <iomanip>
#include <algorithm>
#include <variant>
#include <winsock.h>

#include "BmpFileHeader.h"

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

void PrintBMPInfo(BMPInfo const& bitmapHeader)
{
	std::cout << std::format("Screen Resolution: {}x{}", 
		bitmapHeader.bmpInfoHeader.width, 
		bitmapHeader.bmpInfoHeader.height) << std::endl;

	std::cout << std::format("Count bits per pixel: {}",
		bitmapHeader.bmpInfoHeader.bitCount) << std::endl;

	std::cout << std::format("Image size (bytes): {}",
		bitmapHeader.bmpInfoHeader.sizeImage) << std::endl;

	std::cout << std::format("Compression: {}",
		bitmapHeader.bmpInfoHeader.compression) << std::endl;
}

bool ParseBMPFile(std::ifstream& bmpFile, BMPInfo& bmpInfo)
{
	if (!bmpFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(bmpInfo)))
	{
		return false; // Возникла ошибка при чтении начала BMP-файла
	}

	auto& bmpFH = bmpInfo.bmpFileHeader;

	if (std::memcmp(bmpFH.type, BMP_SIGNATURE_BE, sizeof(BMP_SIGNATURE_BE)) != 0 ||
		std::memcmp(bmpFH.type, BMP_SIGNATURE_LE, sizeof(BMP_SIGNATURE_LE)) != 0)
	{
		return false; // Сигнатура в начале файла не соответствует спецификации BMP
	}

	bmpFH.fileSize = ntohl(bmpFH.fileSize);
	if (bmpFH.fileSize <= 0)
	{
		return false; //Размер файла не может быть отрицательным или пустым
	}

	bmpFH.reserved = ntohl(bmpFH.reserved);
	if (bmpFH.reserved != 0)
	{
		return false; //Размер зарезервированной области должен равняться 0
	}

	auto& bmpIH = bmpInfo.bmpInfoHeader;

	bmpIH.sizeInfoHeader = ntohl(bmpIH.sizeInfoHeader);
	if (bmpIH.sizeInfoHeader != sizeof(BitmapV5Header) &&
		bmpIH.sizeInfoHeader != sizeof(BitmapV4Header) &&
		bmpIH.sizeInfoHeader != sizeof(BitmapInfoHeader)
	)
	{
		return false; // Заголовок не удовлетворяет размерам ни одной из версии
	}

	bmpIH.width = ntohl(bmpIH.width);
	bmpIH.height = ntohl(bmpIH.height);
	if (bmpIH.width == 0 || bmpIH.height == 0)
	{
		return false; // Ни ширина, ни высота BMP-изображения не могут быть равны нулю
	}

	bmpIH.bitCount = ntohl(bmpIH.bitCount);
	if (std::find(AVAILABLE_IMAGE_BITS.begin(), AVAILABLE_IMAGE_BITS.end(), 
		bmpIH.bitCount) == AVAILABLE_IMAGE_BITS.end()
	)
	{
		return false; // Некорректная битность изображения
	}

	bmpIH.sizeImage = ntohl(bmpIH.sizeImage);
	if (bmpIH.sizeImage <= 0)
	{
		return false; //Изображение не может быть отрицательным или пустым
	}

	return true;
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

		BMPInfo bitmapInfo;
		if (ParseBMPFile(bmpFileStream, bitmapInfo)) PrintBMPInfo(bitmapInfo);
		else
		{
			std::cout << "File is not a BMP format file." << std::endl;
			return 1;
		}
	}
	catch (std::logic_error const& err)
	{
		std::cout << err.what() << std::endl;
		return 1;
	}

	return 0;
}