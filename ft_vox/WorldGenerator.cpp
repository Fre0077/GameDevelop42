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
	std::vector<Voxel>	terrain;

	for (int i = 15; i >= 0; i--)
		for (int j = 0; j < 16; j++)
			Voxellator(noisy[((15 - i) * 16) + j], j, i, terrain);
	return terrain;
}

void	WorldGenerator::Voxellator(float point, float x, float y, std::vector<Voxel> &blocks) {
	float				limit;

	if (point < -1.0f) point = -1.0f;
	if (point >  1.0f) point =  1.0f;

	if (point >= -0.3f && point <= 0.3f)
		limit = 128.0f + point * (171.0f / 2.0f);
	else if (point > 0.3f)
	{
		float strength = (point - 0.3f) / 0.7f;
		limit = 128.0f + 0.3f * (171.0f / 2.0f) + strength * (171.0f / 2.0f) * 2.0f;
	} else if (point < -0.3f) {
		float strength = (-0.3f - point) / 0.7f;
		limit = 128.0f + (-0.3f * (171.0f / 2.0f)) - strength * (171.0f / 2.0f);
	} else
		limit = 128.0f;

	for (int i = 0; i < 256; i++) {
		Voxel	block(x, y, i);
		if (i >= limit)
			block.SetTrasparence();
		texture.stone(block);
		blocks.push_back(block);
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

			ret.push_back(value);
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