#include "WorldGenerator.hpp"

WorldGenerator::WorldGenerator(std::string worldName) {
	std::string filePath = "./worlds/" + worldName;
	DIR *dir = opendir(filePath.c_str());
	if (!dir)
		throw UnknownWorld();
	closedir(dir);
	this->worldName = worldName;
	this->data = DataManager();
	this->seed = strUlong(data.getSeed(worldName));
}

WorldGenerator::WorldGenerator(std::string seed, std::string worldName) {
	std::string filePath = "./worlds/" + worldName;
	DIR *dir = opendir(filePath.c_str());
	if (dir) {
		closedir(dir);  
		throw NotNewWorld();
	}
	this->worldName = worldName;
	this->data = DataManager();
	this->seed = strUlong(seed);
	data.saveSeed(seed, worldName);
}

WorldGenerator::~WorldGenerator() {}

void	WorldGenerator::Creation(long x, long y) {
	std::vector<float>	ret = perlinNoise(x - (x % 16), y - (y % 16));
}

Vector WorldGenerator::randomGradient(long x, long y) {
	uint32_t h = this->seed;
	h ^= x * 374761393;
	h ^= y * 668265263;
	h = (h ^ (h >> 13)) * 1274126177;
	h ^= (h >> 16);
	float angle = (h % 360) * (3.1415926f / 180.0f);
	return Vector(std::cos(angle) , std::sin(angle));
}

// 0 bas-sin, 1 bas-des, 2 alt-sin, 3 alt-des
std::vector<Vector>	WorldGenerator::randomVectors(long x, long y) {
	std::vector<Vector> ret;
	ret.push_back(this->randomGradient(x, y));
	ret.push_back(this->randomGradient(x + 16, y));
	ret.push_back(this->randomGradient(x, y + 16));
	ret.push_back(this->randomGradient(x + 16, y + 16));
	return ret;
}

std::vector<float> WorldGenerator::perlinNoise(long x, long y) {
	std::vector<Vector> vectors = randomVectors(x, y);

	// Stampo i 4 vettori "random" generati
	std::cout << "Random gradient vectors:\n";
	for (size_t idx = 0; idx < vectors.size(); idx++) {
		std::cout << "Vector[" << idx << "]: (" << vectors[idx].getX() << ", " << vectors[idx].getY() << ")\n";
	}
	std::cout << std::endl;

	std::vector<float> ret;

	for (int i = 1; i <= 16; i++) {
		for (int j = 1; j <= 16; j++) {
			float dx = i / 16.0f;
			float dy = j / 16.0f;

			//std::cout << "i = " << i << ", j = " << j << "\n";
			//std::cout << "dx = " << dx << ", dy = " << dy << "\n";

			Vector v00(dx, dy);
			Vector v10(dx - 1.0f, dy);
			Vector v01(dx, dy - 1.0f);
			Vector v11(dx - 1.0f, dy - 1.0f);

			// Stampo i vettori temporanei
			//std::cout << "v00 = (" << v00.getX() << ", " << v00.getY() << ")\n";
			//std::cout << "v10 = (" << v10.getX() << ", " << v10.getY() << ")\n";
			//std::cout << "v01 = (" << v01.getX() << ", " << v01.getY() << ")\n";
			//std::cout << "v11 = (" << v11.getX() << ", " << v11.getY() << ")\n";

			float d00 = vectors[0].prod(v00);
			float d10 = vectors[1].prod(v10);
			float d01 = vectors[2].prod(v01);
			float d11 = vectors[3].prod(v11);

			//std::cout << "d00 = " << d00 << "\n";
			//std::cout << "d10 = " << d10 << "\n";
			//std::cout << "d01 = " << d01 << "\n";
			//std::cout << "d11 = " << d11 << "\n";

			float u = this->Smoother(dx);
			float v = this->Smoother(dy);

			//std::cout << "u (Smoother(dx)) = " << u << "\n";
			//std::cout << "v (Smoother(dy)) = " << v << "\n";

			float ix0 = this->Midder(d00, d10, u);
			float ix1 = this->Midder(d01, d11, u);

			//std::cout << "ix0 = Midder(d00, d10, u) = " << ix0 << "\n";
			//std::cout << "ix1 = Midder(d01, d11, u) = " << ix1 << "\n";

			float value = this->Midder(ix0, ix1, v);
			//std::cout << "final value = Midder(ix0, ix1, v) = " << value << "\n\n";

			ret.push_back(value);

			//if (j == 10)
			//	break;
		}
		//break;
	}
	printVec(ret);
	return ret;
}

float	WorldGenerator::Midder(float a, float b, float val) {
	return (a + val * (b - a));
}

float	WorldGenerator::Smoother(float val) {
	return val * val * val * (val * (val * 6 - 15) + 10);
}

unsigned long	WorldGenerator::strUlong(std::string input) {
	unsigned long result = 0;
    for (char c : input)
        result = result * 10 + (c - '0');
    return result;
}