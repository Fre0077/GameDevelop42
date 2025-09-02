#pragma once

# include "utils/Voxel.hpp"
class Voxel;

class Texture {
public:
	Texture();
	~Texture();

	void	spruce_plank(Voxel &block);
	void	cooclestone(Voxel &block);
	void	stone(Voxel &block);
	void	grass(Voxel &block);
};