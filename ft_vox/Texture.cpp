#include "Texture.hpp"

Texture::Texture() {}

Texture::~Texture() {}

void	setUV(Vertex &one, Vertex &two, Vertex &three1, Vertex &three2, Voxel &block) {
	one.u = block.tex[0].u;
	one.v = block.tex[0].v;
	two.u = block.tex[0].u + 1.0f / 64.0f;
	two.v = block.tex[0].v + 1.0f / 32.0f;
	three1.u = block.tex[0].u + 1.0f / 64.0f;
	three1.v = block.tex[0].v;
	three2.u = block.tex[0].u;
	three2.v = block.tex[0].v + 1.0f / 32.0f;
}

void	Texture::cooclestone(Voxel &block) {
	block.tex[0] = {13, 14};
	block.tex[1] = {13, 14};
	block.tex[2] = {13, 14};
	block.tex[3] = {13, 14};
	block.tex[4] = {13, 14};
	block.tex[5] = {13, 14};
}

void	Texture::stone(Voxel &block) {
	block.tex[0] = {6, 26};
	block.tex[1] = {6, 26};
	block.tex[2] = {6, 26};
	block.tex[3] = {6, 26};
	block.tex[4] = {6, 26};
	block.tex[5] = {6, 26};
}
