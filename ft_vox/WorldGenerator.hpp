#pragma once

# include "DataManager.hpp"
class DataManager;
# include "Texture.hpp"
class Texture;
# include "utils/Vector.hpp"
class Vector;
# include "utils/Voxel.hpp"
class Voxel;

class WorldGenerator {
private:
	unsigned long	seed;
	std::string		worldName;
	DataManager		data;
	Texture			texture;

public:

	WorldGenerator(std::string seed, std::string worldName);
	~WorldGenerator();

	std::vector<Voxel>	Creation(long z, long x);
	void				Voxellator(float point, int X, int Z, int x, int z, std::vector<Voxel> &blocks);
	
	std::vector<Vector>	randomVectors(long x, long y);
	std::vector<float>	perlinNoise(long x, long y);
	unsigned long		strUlong(std::string input);
	Vector				randomGradient(long x, long y);
	float				Midder(float a, float b, float val);
	float				Smoother(float val);
};
