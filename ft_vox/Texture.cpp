#include "Texture.hpp"

Texture::Texture() {}

Texture::~Texture() {}

void	Texture::setUV(Vertex &one, Vertex &two, Vertex &three1, Vertex &three2, Voxel &block) {
	one.u = block.texture[0].u * 1.0f / 64.0f;
	one.v = block.texture[0].v * 1.0f / 32.0f;
	two.u = (block.texture[0].u + 1.0f / 64.0f) * 1.0f / 64.0f;
	two.v = (block.texture[0].v + 1.0f / 32.0f) * 1.0f / 32.0f;
	three1.u = (block.texture[0].u + 1.0f / 64.0f) * 1.0f / 64.0f;
	three1.v = block.texture[0].v * 1.0f / 32.0f;
	three2.u = block.texture[0].u * 1.0f / 64.0f;
	three2.v = (block.texture[0].v + 1.0f / 32.0f) * 1.0f / 32.0f;
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
	block.texture[0] = {6, 26};
	block.texture[1] = {6, 26};
	block.texture[2] = {6, 26};
	block.texture[3] = {6, 26};
	block.texture[4] = {6, 26};
	block.texture[5] = {6, 26};
}
