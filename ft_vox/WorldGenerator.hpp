#pragma once
# include "headers/struct.h"
# include "headers/utils.h"
# include "DataManager.hpp"
# include "utils/Voxel.hpp"
# include "utils/Vector.hpp"

class Voxel;
class Vector;
class DataManager;

class WorldGenerator {
private:
	unsigned long	seed;
	std::string		worldName;
	DataManager		data;

public:

	WorldGenerator(std::string seed, std::string worldName);
	WorldGenerator(std::string worldName);
	~WorldGenerator();

	std::vector<Vector>	randomVectors(long x, long y);
	std::vector<float>	perlinNoise(long x, long y);
	unsigned long		strUlong(std::string input);
	Vector				randomGradient(long x, long y);
	float				Midder(float a, float b, float val);
	float				Smoother(float val);
	void				Creation(long x, long y);

	class NotNewWorld : public std::exception {
	public:
		const char* what() const noexcept override {
			return "WorldGenerator: A world with this name allready exist";
		}
	};

	class UnknownWorld : public std::exception {
	public:
		const char* what() const noexcept override {
			return "WorldGenerator: The world doesn't exist";
		}
	};
};
