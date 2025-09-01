#include "../headers/inclusion.h"

void	printVec(const std::vector<float>& vec) {
	if (vec.size() != 256) {
		std::cerr << "Vector must contain exactly 256 elements (16x16).\n";
		return;
	}

	const char* levels = " .:-=+*#%@";

	for (int i = 0; i < 256; i++) {
		float val = vec[i];
		val = (val - 1.0f) / 2.0f;
		int level = std::min(9, std::max(0, static_cast<int>(val * 9)));
		std::cout << levels[level] << " ";
		if (i % 16 == 0)
			std::cout << std::endl;
	}
}

void	printVecF(const std::vector<float>& vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
}

void	pushVertex(Vertex &ver, std::vector<float> &vec) {
	vec.push_back(ver.x);
	vec.push_back(ver.y);
	vec.push_back(ver.z);
	vec.push_back(ver.u);
	vec.push_back(ver.v);
}

int	index(int x, int y, int z) {
	return (y * 16 * 16) + (z * 16) + x;
}

bool cicle(int &x, int &y, int &z) {
	y++;
	if (y >= 256) {
		y = 0;
		x++;
		if (x >= 16) {
			x = 0;
			z++;
			if (z >= 16)
				return false;
		}
	}
	return true;
}