#pragma once

static const std::vector<uint16_t> AVAILABLE_BMP_SIGNATURE = { 0x424D, 0x4D42 };
static const std::vector<uint16_t> AVAILABLE_IMAGE_BITS = { 1, 2, 4, 8, 16, 24, 32, 48, 64 };

enum class BMPCompression : uint32_t
{
	RGB = 0,
	RLE_8,
	RLE_4,
	BIT_FIELDS,
	JPEG,
	PNG,
	ALPHA_BIT_FIELDS
};

#pragma pack (push, 1)
struct XYZColor
{
	int32_t red;
	int32_t green;
	int32_t blue;
};
struct XYZColorTriple
{
	XYZColor xyzRed;
	XYZColor xyzGreen;
	XYZColor xyzBlue;
};
struct BitmapFileHeader
{
	uint16_t type;
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
	XYZColorTriple endpoints;
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