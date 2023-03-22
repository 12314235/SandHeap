#pragma once
#include <deque>
#include <string>

class Canvas {
public:
	std::deque<std::deque<uint64_t>> canvas;
	std::deque<std::deque<uint64_t>> old_canvas;

	Canvas(uint64_t width, uint64_t height, const std::string& path_output);

	void Resize();
	bool NextIteration(std::string& output_path, int iteration, int max_iter, int freq);
};