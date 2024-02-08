#pragma once
#include <cstdint>
#include <array>

static const uint8_t BMP_SIGNATURE[] = { 0x42, 0x4D };

enum class BMPCompression : uint16_t
{
	RGB = 0,
	RLE8 = 1,
	RLE4 = 2,
	BITFIELDS = 3,
	JPEG = 4,
	PNG = 5,
	ALPHABITFIELDS = 6,
	CMYK = 11,
	CMYKRLE8 = 12,
	CMYKRLE4 = 13
};

#pragma pack (push, 1)
struct BitmapFileHeader
{
	uint8_t signature[sizeof(BMP_SIGNATURE)];
	uint32_t size;
	uint32_t reserved;
	uint32_t offBits;
};
struct BitmapInfoHeader
{
	uint32_t size;
	int32_t width;
	int32_t height;
	uint16_t planes;
	uint16_t bitCount;
	BMPCompression compression;
	uint32_t sizeImage;
	int32_t xPelsPerMeter;
	int32_t yPelsPerMeter;
	uint32_t colorUsed;
	uint32_t colorImportant;
};
struct BMPInfo
{
	BitmapFileHeader bmpFileHeader;
	BitmapInfoHeader bmpInfoHeader;
};
#pragma pack (pop)