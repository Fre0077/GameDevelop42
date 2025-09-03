#pragma once

# include "EightBool.hpp"

class EightBool; // 0-5 vis blocco 6 semi-trasparente

class Voxel {
private:
	EightBool	vis;
	Face	face[6];
	
public:
	uint8_t		block;
	tex		texture[6];
	Voxel();
	~Voxel();

	std::vector<Vertex>	GetVertex();

	uint8_t	GetFace(uint8_t n);
	uint8_t	GetTrasparence();

	void	calculateTriangle(float x, float y, float z);
	void	SetFace(uint8_t n);
	void	SetTrasparence();
	void	setUV(int Face);
};

std::ostream& operator<<(std::ostream& out, Voxel &rhs);

// Per il texture: se contiene 1, allora ogni facica è uguale, se due è come un log, se no ci saranno tutte le faccie

