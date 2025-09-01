#include "WorldGenerator.hpp"

WorldGenerator::WorldGenerator(std::string seed, std::string worldName) {
	std::string filePath = "./worlds/" + worldName;
	DIR *dir = opendir(filePath.c_str());
	this->worldName = worldName;
	this->data = DataManager();
	if (dir) {
		closedir(dir);
		this->seed = strUlong(data.getSeed(worldName));
	} else {
		this->seed = strUlong(seed);
		data.saveSeed(seed, worldName);
	}
}

WorldGenerator::~WorldGenerator() {}

std::vector<Voxel>	WorldGenerator::Creation(long x, long y) {
	std::vector<float>	noisy = perlinNoise(x - (x % 16), y - (y % 16));
	//printVec(noisy);
	std::vector<Voxel>	chunck(CHUNCK);

	for (int X = 15; X >= 0; X--)
		for (int Z = 0; Z < 16; Z++)
			Voxellator(noisy[((15 - X) * 16) + Z], Z, X, chunck);
	
	return chunck;
}

void	WorldGenerator::Voxellator(float point, int x, int z, std::vector<Voxel> &blocks) {
	float	limit = point * 80;
	(void) point;

	//std::cout << point << std::endl;

	//if (point >= 0.7f && point <= 1.3f)
	//	limit = 128.0f + point * (171.0f / 2.0f);
	//else if (point > 1.3f)
	//{
	//	float strength = (point - 0.3f) / 0.7f;
	//	limit = 128.0f + 0.3f * (171.0f / 2.0f) + strength * (171.0f / 2.0f) * 2.0f;
	//} else if (point < 0.7f) {
	//	float strength = (-0.3f - point) / 0.7f;
	//	limit = 128.0f + (-0.3f * (171.0f / 2.0f)) - strength * (171.0f / 2.0f);
	//} else
	//	limit = 128.0f;

	//std::cout << limit << std::endl;
	int i;
	for (int y = 0; y < 256; y++) {
		i = index(x, y, z);
		if (y >= limit)
			blocks[i].SetTrasparence();
		texture.spruce_plank(blocks[i]);
		blocks[i].calculateTriangle(x, y, z);
	}
}

std::vector<float> WorldGenerator::perlinNoise(long x, long y) {
	std::vector<Vector> vectors = randomVectors(x, y);
	std::vector<float> ret;

	for (float i = 15.5f; i > 0; i--) {
		for (float j = 0.5f; j < 16; j++) {
			float dx = j / 16.0f;
			float dy = i / 16.0f;

			Vector v00(dx, dy);
			Vector v10(dx - 1.0f, dy);
			Vector v01(dx, dy - 1.0f);
			Vector v11(dx - 1.0f, dy - 1.0f);

			float d00 = vectors[0].prod(v00);
			float d10 = vectors[1].prod(v10);
			float d01 = vectors[2].prod(v01);
			float d11 = vectors[3].prod(v11);

			float u = this->Smoother(dx);
			float v = this->Smoother(dy);

			float ix0 = this->Midder(d00, d10, u);
			float ix1 = this->Midder(d01, d11, u);

			float value = this->Midder(ix0, ix1, v);

			ret.push_back(value + 2);
		}
	}
	return ret;
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