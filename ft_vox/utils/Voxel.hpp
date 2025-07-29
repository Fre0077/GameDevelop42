#pragma once

# include "EightBool.hpp"

class EightBool; // 0-5 vis blocco 6 trasparente 7 semi-trasparente

class Voxel {
private:
	EightBool	vis;
	uint8_t		block;
	Pos			voxel;
public:
	tex tex[6];
	Voxel(float x, float y, float z);
	~Voxel();

	void	SetFace(uint8_t n);
	void	SetTrasparence();

	uint8_t	GetFace(uint8_t n);
	uint8_t	GetTrasparence();
	Pos		GetVoxel();
};

// Per il tex: se contiene 1, allora ogni facica è uguale, se due è come un log, se no ci saranno tutte le faccie

