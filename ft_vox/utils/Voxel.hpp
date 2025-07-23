#pragma once

# include "../headers/struct.h"
# include "EightBool.hpp"

class EightBool; // 0-5 vis blocco, 6 trasparenza

class Voxel {
private:
	EightBool	vis;
	Vertex		voxel;
	int			texture;
public:
	Voxel(float x, float y, float z);
	~Voxel();

	void	SetTexture(int input);
	void	SetFace(uint8_t n);
	void	SetTrasparence();

	uint8_t	GetFace(uint8_t n);
	uint8_t	GetTrasparence();
	Vertex	GetVoxel();
	int		GetTexture();
};
