#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "Canvas.h"

int main(int argc, char** argv) {
	std::FILE file_input;

	uint64_t width = 0;
	uint64_t height = 0;
	int max_iter = 0;
	int freq = 0;
	std::string path_input = "";
	std::string path_output = "";

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--length")) { height = std::stoll(argv[i + 1]); }
		else if (!strcmp(argv[i], "-w") || !strcmp(argv[i], "--width")) { width = std::stoll(argv[i + 1]); }
		else if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--input")) { path_input = argv[i + 1]; }
		else if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) { path_output = argv[i + 1]; }
		else if (!strcmp(argv[i], "-m") || !strcmp(argv[i], "--max-iter")) { max_iter = std::stoll(argv[i + 1]); }
		else if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--freq")) { freq = std::stoll(argv[i + 1]); }
	}

	Canvas canvas(width, height, path_input);

	int counter = 0;

	while (!canvas.NextIteration(path_output, counter, max_iter, freq)) { counter++; }

}