#include "Voxel.hpp"

Voxel::Voxel() {
	this->texture[0] = {0, 0};
	this->texture[1] = {0, 0};
	this->texture[2] = {0, 0};
	this->texture[3] = {0, 0};
	this->texture[4] = {0, 0};
	this->texture[5] = {0, 0};
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
	return 0;
}

uint8_t	Voxel::GetFace(uint8_t n) {
	return vis.GetBool(n);
}

std::ostream& operator<<(std::ostream& out, Voxel &rhs)
{
	if (rhs.GetTrasparence())
		out << "o";
	else
		out << "i";
	return out;
}