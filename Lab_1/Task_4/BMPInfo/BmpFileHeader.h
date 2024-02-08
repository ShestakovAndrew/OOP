#pragma once
#include <cstdint>
#include <array>

static const uint8_t BMP_SIGNATURE_BE[] = { 0x42, 0x4D };
static const uint8_t BMP_SIGNATURE_LE[] = { 0x4D, 0x42 };
static const std::vector<uint16_t> AVAILABLE_IMAGE_BITS = { 1, 2, 4, 8, 16, 24, 32, 48, 64 };

enum class BMPCompression : uint16_t
{
	RGB = 0,
	RLE_8 = 1,
	RLE_4 = 2,
	BIT_FIELDS = 3,
	JPEG = 4,
	PNG = 5,
	ALPHA_BIT_FIELDS = 6
};

#pragma pack (push, 1)
struct BitmapFileHeader
{
	uint8_t type[sizeof(BMP_SIGNATURE_BE)];
	uint32_t fileSize;
	uint32_t reserved;
	uint32_t offBits;
};
struct BitmapInfoHeader
{
	uint32_t sizeInfoHeader;
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
struct BitmapV4Header : BitmapInfoHeader
{
	uint32_t redMask;
	uint32_t greenMask;
	uint32_t blueMask;
	uint32_t alphaMask;
	uint32_t csType;
	CIEXYZTRIPLE endpoints;
	uint32_t gammaRed;
	uint32_t gammaGreen;
	uint32_t gammaBlue;
};
struct BitmapV5Header : BitmapV4Header
{
	uint32_t intent;
	uint32_t profileData;
	uint32_t profileSize;
	uint32_t reserved;
};
struct BMPInfo
{
	BitmapFileHeader bmpFileHeader;
	BitmapV5Header bmpInfoHeader;
};
#pragma pack (pop)