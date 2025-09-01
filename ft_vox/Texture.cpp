#include "Texture.hpp"

Texture::Texture() {}

Texture::~Texture() {}

void	Texture::cooclestone(Voxel &block) {
	block.texture[0] = {13, 14};
	block.texture[1] = {13, 14};
	block.texture[2] = {13, 14};
	block.texture[3] = {13, 14};
	block.texture[4] = {13, 14};
	block.texture[5] = {13, 14};
}

void	Texture::stone(Voxel &block) {
	block.texture[0] = {6, 5};
	block.texture[1] = {6, 5};
	block.texture[2] = {6, 5};
	block.texture[3] = {6, 5};
	block.texture[4] = {6, 5};
	block.texture[5] = {6, 5};
}

void	Texture::spruce_plank(Voxel &block) {
	block.texture[0] = {3, 5};
	block.texture[1] = {3, 5};
	block.texture[2] = {3, 5};
	block.texture[3] = {3, 5};
	block.texture[4] = {3, 5};
	block.texture[5] = {3, 5};
}