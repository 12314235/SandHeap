#include "Image.h"
#include <iostream>
#include <fstream>

Color::Color()
	:r(0), g(0), b(0)
{
}

Color::Color(int r, int g, int b)
	:r(r), g(g), b(b)
{
}

Color::~Color()
{
}

Image::Image(uint32_t width, uint32_t height)
	:m_width(width), m_height(height), m_colors(std::vector<Color>(width* height))
{
}

Image::~Image()
{
}

Color Image::GetColor(int x, int y) const
{
	return m_colors[y * m_width + x];
}

void Image::SetColor(const Color& color, int x, int y)
{
	m_colors[y * m_width + x].r = color.r;
	m_colors[y * m_width + x].g = color.g;
	m_colors[y * m_width + x].b = color.b;
}

void Image::Export(const std::string& path)
{
	std::ofstream f;
	f.open(path, std::ios::out | std::ios::binary);

	if (!f.is_open()) {
		std::cout << "File could not be opened\n";
		return;
	}

	unsigned char bmpPad[3] = { 0,0,0 };
	const int paddingAmount = (4 - (m_width * 3) % 4) % 4;

	const int FileHeaderSize = 14;
	const int InformationHeaderSize = 40;
	const size_t fileSize = FileHeaderSize + InformationHeaderSize + m_width * m_height * 3 + paddingAmount * m_width;

	unsigned char fileHeader[FileHeaderSize];

	//File Type
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';

	//File Size
	fileHeader[2] = fileSize;
	fileHeader[3] = fileSize >> 8;
	fileHeader[4] = fileSize >> 16;
	fileHeader[5] = fileSize >> 24;

	//Reserved
	fileHeader[6] = 0;
	fileHeader[7] = 0;
	fileHeader[8] = 0;
	fileHeader[9] = 0;

	//Pixel Data Offset
	fileHeader[10] = FileHeaderSize * InformationHeaderSize;
	fileHeader[11] = 0;
	fileHeader[12] = 0;
	fileHeader[13] = 0;

	unsigned char InformationHeader[InformationHeaderSize];

	//Header size
	InformationHeader[0] = InformationHeaderSize;
	InformationHeader[1] = 0;
	InformationHeader[2] = 0;
	InformationHeader[3] = 0;

	//Image Width
	InformationHeader[4] = m_width;
	InformationHeader[5] = m_width >> 8;
	InformationHeader[6] = m_width >> 16;
	InformationHeader[7] = m_width >> 24;

	//Image Height
	InformationHeader[8] = m_height;
	InformationHeader[9] = m_height >> 8;
	InformationHeader[10] = m_height >> 16;
	InformationHeader[11] = m_height >> 24;

	//Planes
	InformationHeader[12] = 1;
	InformationHeader[13] = 0;

	//Bits Per Pixel
	InformationHeader[14] = 24;
	InformationHeader[15] = 0;

	//Compression
	InformationHeader[16] = 0;
	InformationHeader[17] = 0;
	InformationHeader[18] = 0;
	InformationHeader[19] = 0;

	//Image Size
	InformationHeader[20] = 0;
	InformationHeader[21] = 0;
	InformationHeader[22] = 0;
	InformationHeader[23] = 0;

	//X pixels per meter
	InformationHeader[24] = 0;
	InformationHeader[25] = 0;
	InformationHeader[26] = 0;
	InformationHeader[27] = 0;

	//Y pixels per meter
	InformationHeader[28] = 0;
	InformationHeader[29] = 0;
	InformationHeader[30] = 0;
	InformationHeader[31] = 0;

	//Total Colors
	InformationHeader[32] = 0;
	InformationHeader[33] = 0;
	InformationHeader[34] = 0;
	InformationHeader[35] = 0;

	//Important Colors
	InformationHeader[36] = 0;
	InformationHeader[37] = 0;
	InformationHeader[38] = 0;
	InformationHeader[39] = 0;

	f.write(reinterpret_cast<char*>(fileHeader), FileHeaderSize);
	f.write(reinterpret_cast<char*>(InformationHeader), InformationHeaderSize);

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255);
			unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255);
			unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255);

			unsigned char color[] = { b, g, r };

			f.write(reinterpret_cast<char*>(color), 3);
		}

		f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
	}

	f.close();
	std::cout << "File created" << '\n';
}

Color ÑellColor(uint64_t grain_amount)
{
	Color ñell_color;
	switch (grain_amount) {
	case 0:
		ñell_color.r = 1;
		ñell_color.g = 1;
		ñell_color.b = 1;
		break;
	case 1:
		ñell_color.r = 256;
		ñell_color.g = 103;
		ñell_color.b = 180;
		break;
	case 2:
		ñell_color.r = 154;
		ñell_color.g = 256;
		ñell_color.b = 52;
		break;
	case 3:
		ñell_color.r = 1;
		ñell_color.g = 1;
		ñell_color.b = 256;
		break;
	default:
		ñell_color.r = 256;
		ñell_color.g = 256;
		ñell_color.b = 256;
		break;
	}

	return ñell_color;
}

void CreateImage(uint64_t width, uint64_t height, const std::deque<std::deque<uint64_t>>& canvas, const std::string& output_path)
{
	Image image(width, height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			image.SetColor(ÑellColor(canvas[x][y]), x, y);
		}
	}

	image.Export(output_path);
}