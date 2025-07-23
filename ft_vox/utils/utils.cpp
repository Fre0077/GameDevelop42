#include "../headers/utils.h"

void	printVec(const std::vector<float>& vec) {
	if (vec.size() != 256) {
		std::cerr << "Vector must contain exactly 256 elements (16x16).\n";
		return;
	}

	const char* levels = " .:-=+*#%@";

	for (int row = 15; row >= 0; row--) {
		for (int col = 0; col < 16; col++) {
			int index = col * 16 + row;
			float val = vec[index];
			val = (val + 1.0f) / 2.0f;
			int level = std::min(9, std::max(0, static_cast<int>(val * 9)));
			std::cout << levels[level] << " ";
		}
		std::cout << std::endl;
	}
}