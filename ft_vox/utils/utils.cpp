#include "../headers/inclusion.h"

void	printVec(const std::vector<float>& vec) {
	if (vec.size() != 256) {
		std::cerr << "Vector must contain exactly 256 elements (16x16).\n";
		return;
	}

	const char* levels = " .:-=+*#%@";

	for (int i = 0; i < 256; i++) {
		float val = vec[i];
		val = (val + 1.0f) / 2.0f;
		int level = std::min(9, std::max(0, static_cast<int>(val * 9)));
		std::cout << levels[level] << " ";
		if (i % 16 == 0)
			std::cout << std::endl;
	}
}