#pragma once

#include <deque>
#include <vector>
#include <string>

struct Color {
	int r, g, b;

	Color();
	Color(int r, int g, int b);
	~Color();
};

class Image {
public:
	Image(uint32_t width, uint32_t height);
	~Image();

	Color GetColor(int x, int y) const;
	void SetColor(const Color& color, int x, int y);

	void Export(const std::string& path);

private:
	uint32_t m_width;
	uint32_t m_height;
	std::vector<Color> m_colors;
};

void CreateImage(uint64_t width, uint64_t height, const std::deque<std::deque<uint64_t>>& canvas, const std::string& output_path);

Color ÑellColor(uint64_t grain_amount);