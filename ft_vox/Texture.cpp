#include "Texture.hpp"

Texture::Texture() {}

Texture::~Texture() {}

void	Texture::setTexture(int i, Voxel &block) {
	switch (i) {
		case AIR: break;
		case STONE: this->stone(block); break;
		case GRASS: this->grass(block); break;
		default:
			std::cerr << "Texture: unkhonw block tipe " << i << std::endl;
			break;
	}
}

void	Texture::stone(Voxel &block) {
	block.block = 1;
	block.texture[0] = {6, 5};
	block.texture[1] = {6, 5};
	block.texture[2] = {6, 5};
	block.texture[3] = {6, 5};
	block.texture[4] = {6, 5};
	block.texture[5] = {6, 5};
}

void	Texture::grass(Voxel &block) {
	block.block = 2;
	block.texture[0] = {25, 23};
	block.texture[1] = {25, 23};
	block.texture[2] = {21, 18};
	block.texture[3] = {26, 21};
	block.texture[4] = {25, 23};
	block.texture[5] = {25, 23};
}

void	Texture::cooclestone(Voxel &block) {
	block.texture[0] = {13, 14};
	block.texture[1] = {13, 14};
	block.texture[2] = {13, 14};
	block.texture[3] = {13, 14};
	block.texture[4] = {13, 14};
	block.texture[5] = {13, 14};
}

void	Texture::spruce_plank(Voxel &block) {
	block.texture[0] = {3, 5};
	block.texture[1] = {3, 5};
	block.texture[2] = {3, 5};
	block.texture[3] = {3, 5};
	block.texture[4] = {3, 5};
	block.texture[5] = {3, 5};
}