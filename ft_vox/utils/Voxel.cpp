#include "Voxel.hpp"

Voxel::Voxel(float x, float y, float z) {
	voxel.x = x;
	voxel.y = y;
	voxel.z = z;
	this->tex[0] = {0, 0};
	this->tex[1] = {0, 0};
	this->tex[2] = {0, 0};
	this->tex[3] = {0, 0};
	this->tex[4] = {0, 0};
	this->tex[5] = {0, 0};
}

Voxel::~Voxel() {}

void	Voxel::SetFace(uint8_t n) {
	vis.SetBool(n);
}

void	Voxel::SetTrasparence() {
	vis.SetBool(6);
}

uint8_t	Voxel::GetTrasparence() {
	if (vis.GetBool(6) || vis.GetValue() == 192)
		return 1;
}

uint8_t	Voxel::GetFace(uint8_t n) {
	return vis.GetBool(n);
}

Pos	Voxel::GetVoxel() {
	return voxel;
}