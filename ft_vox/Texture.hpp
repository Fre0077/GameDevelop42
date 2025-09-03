#pragma once

# include "utils/Voxel.hpp"
class Voxel;

enum BlockType {
    AIR = 0,
    STONE = 1,
    GRASS  = 2
};

class Texture {
public:
	Texture();
	~Texture();

	void	setTexture(int i, Voxel &block);

	void	spruce_plank(Voxel &block);
	void	cooclestone(Voxel &block);
	void	stone(Voxel &block);
	void	grass(Voxel &block);
};

//2 = sotto
//3 = sopra