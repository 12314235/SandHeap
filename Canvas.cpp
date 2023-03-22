#include "Canvas.h"
#include "Image.h"
#include <fstream>
#include <string>
#include <iostream>

Canvas::Canvas(uint64_t width, uint64_t height, const std::string& input_path) {
	canvas.resize(height, std::deque<uint64_t>(width, 0));

	std::fstream f;
	f.open(input_path, std::ios::in, std::ios::binary);

	std::string current;
	std::string buff = "";
	uint64_t inp[2] = { 0, 0 };
	int counter = 0;

	while (std::getline(f, current, '\n')) {
		for (int i = 0; i <= current.size(); i++) {
			if (i == current.size()) {
				canvas[inp[0]][inp[1]] = std::stoll(buff);
				buff = "";
				counter = 0;
				continue;
			}
			else if (current[i] == '\t') {
				inp[counter] = std::stoi(buff);
				counter++;
				buff = "";
				continue;
			}
			else {
				buff += current[i];
			}
		}
	}

}

void Canvas::Resize()
{
	for (int x = 0; x < canvas[0].size(); x++) {
		if (canvas[0][x] > 3) {
			canvas.push_front(std::deque<uint64_t>(canvas[0].size(), 0));
			break;
		}
	}

	for (int x = 0; x < canvas[0].size(); x++) {
		if (canvas[canvas.size() - 1][x] > 3) {
			canvas.push_back(std::deque<uint64_t>(canvas[0].size(), 0));
			break;
		}
	}

	for (int y = 0; y < canvas.size(); y++) {
		if (canvas[y][0] > 3) {
			for (int i = 0; i < canvas.size(); i++) {
				canvas[i].push_front(0);
			}
			break;
		}
	}

	for (int y = 0; y < canvas.size(); y++) {
		if (canvas[y][canvas[0].size() - 1] > 3) {
			for (int i = 0; i < canvas.size(); i++) {
				canvas[i].push_back(0);
			}
			break;
		}
	}
}

bool Canvas::NextIteration(std::string& output_path, int iteration, int max_iter, int freq) {
	bool is_stable = true;
	std::string output_iter = "";

	Resize();

	old_canvas = canvas;

	for (int y = 1; y < canvas.size() - 1; y++) {
		for (int x = 1; x < canvas[y].size() - 1; x++) {
			if (old_canvas[x][y] > 3) {
				canvas[x][y] -= 4;
				canvas[x + 1][y] += 1;
				canvas[x - 1][y] += 1;
				canvas[x][y + 1] += 1;
				canvas[x][y - 1] += 1;
				is_stable = false;
			}
		}
	}

	if (is_stable || iteration == max_iter) {
		CreateImage(canvas.size(), canvas[0].size(), canvas, output_path + "\\output.bmp");
		is_stable = true;
	}
	else if (freq != 0 && iteration % freq == 0) {
		output_iter = std::to_string(iteration) + ".bmp";
		CreateImage(canvas.size(), canvas[0].size(), canvas, output_path + "\\" + output_iter);
	}


	return is_stable;
}
