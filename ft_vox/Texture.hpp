#pragma once

# include "headers/struct.h"
# include "headers/utils.h"

# include "utils/Voxel.hpp"
class Voxel;

class Texture {
public:
	Texture();
	~Texture();

	void	setUV(Vertex &one, Vertex &two, Vertex &three1, Vertex &three2, Voxel &block);
	void	cooclestone(Voxel &block);
	void	stone(Voxel &block);
};

//0 = stone
//1 = cobblestone