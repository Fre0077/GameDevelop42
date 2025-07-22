#include "Voxel.hpp"

Voxel::Voxel(float x, float y, float z) {
	voxel.x = x;
	voxel.y = y;
	voxel.z = z;
}

Voxel::~Voxel() {}


void	Voxel::SetTexture(int input) {
	texture = input;
}

void	Voxel::SetFace(uint8_t n) {
	vis.SetBool(n);
}

void	Voxel::SetTrasparence() {
	vis.SetBool(6);
}

uint8_t	Voxel::GetTrasparence() {
	return vis.GetBool(6);
}

uint8_t	Voxel::GetFace(uint8_t n) {
	return vis.GetBool(n);
}

Vertex	Voxel::GetVoxel() {
	return voxel;
}

int		Voxel::GetTexture() {
	return texture;
}
