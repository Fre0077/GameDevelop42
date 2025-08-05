#include "Texture.hpp"

Texture::Texture() {}

Texture::~Texture() {}

void	Texture::setUV(Vertex &one, Vertex &two, Vertex &three1, Vertex &three2, Voxel &block, int face) {
	one.u = block.texture[face].u * Xtex;
	one.v = block.texture[face].v * Ytex;
	two.u = (block.texture[face].u + 1) * Xtex;
	two.v = (block.texture[face].v + 1) * Ytex;
	three1.u = (block.texture[face].u + 1) * Xtex;
	three1.v = block.texture[face].v * Ytex;
	three2.u = block.texture[face].u * Xtex;
	three2.v = (block.texture[face].v + 1) * Ytex;
}

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
