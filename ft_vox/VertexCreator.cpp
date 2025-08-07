#include "VertexCreator.hpp"

VertexCreator::VertexCreator() {}

VertexCreator::~VertexCreator() {}

void	VertexCreator::calculateTriangle() {
	Vertex	one, two, three1, three2;
	float	x = 0, y = -1, z = 0;

	while (cicle(x, y, z)) {
		if (blocks[index(x, y, z)].GetFace(0)) {
			one = {x, y, z, 0, 0};
			two = {one.x + 1, one.y + 1, one.z, 0, 0};
			three1 = {one.x, one.y + 1, one.z, 0, 0};
			three2 = {one.x + 1, one.y, one.z, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[index(x, y, z)], 0);
		} else if (blocks[index(x, y, z)].GetFace(5)) {
			one = {x + 1, y + 1, z + 1, 0, 0};
			two = {x, y, one.z, 0, 0};
			three1 = {one.x, y, one.z, 0, 0};
			three2 = {x, one.y, one.z, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[index(x, y, z)], 5);
		}
		pushVertex(three1, triangles);
		pushVertex(one, triangles);
		pushVertex(two, triangles);
		pushVertex(three2, triangles);
		pushVertex(one, triangles);
		pushVertex(two, triangles);
		if (blocks[index(x, y, z)].GetFace(1)) {
			one = {x, y, z, 0, 0};
			two = {one.x + 1, one.y, one.z + 1, 0, 0};
			three1 = {one.x, one.y, one.z + 1, 0, 0};
			three2 = {one.x + 1, one.y, one.z, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[index(x, y, z)], 1);
		} else if (blocks[index(x, y, z)].GetFace(3)) {
			one = {x + 1, y + 1, z + 1, 0, 0};
			two = {x, one.y, z, 0, 0};
			three1 = {one.x, one.y, z, 0, 0};
			three2 = {x, one.y, one.z, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[index(x, y, z)], 3);
		}
		pushVertex(three1, triangles);
		pushVertex(one, triangles);
		pushVertex(two, triangles);
		pushVertex(three2, triangles);
		pushVertex(one, triangles);
		pushVertex(two, triangles);
		if (blocks[index(x, y, z)].GetFace(2)) {
			one = {x + 1, y + 1, z + 1, 0, 0};
			two = {one.x, y, z, 0, 0};
			three1 = {one.x, y, one.z, 0, 0};
			three2 = {one.x, one.y, z, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[index(x, y, z)], 2);
		} else if (blocks[index(x, y, z)].GetFace(4)) {
			one = {x, y, z, 0, 0};
			two = {one.x, one.y + 1, one.z + 1, 0, 0};
			three1 = {one.x, one.y + 1, one.z, 0, 0};
			three2 = {one.x, one.y, one.z + 1, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[index(x, y, z)], 4);
		}
		pushVertex(three1, triangles);
		pushVertex(one, triangles);
		pushVertex(two, triangles);
		pushVertex(three2, triangles);
		pushVertex(one, triangles);
		pushVertex(two, triangles);
	}
}

void	VertexCreator::setBlocks(std::vector<Voxel> &input) {
	this->blocks = input;
}

//void	VertexCreator::fovCheck() {
	
//}

void	VertexCreator::directionCheck(float X, float Y, float Z) {
	float	x = 0, y = -1, z = 0;

	while (cicle(x, y, z)) {
		if (x < X)
			blocks[index(x, y, z)].SetFace(4);
		else
			blocks[index(x, y, z)].SetFace(2);
		if (y < Y)
			blocks[index(x, y, z)].SetFace(1);
		else
			blocks[index(x, y, z)].SetFace(3);
		if (z < Z)
			blocks[index(x, y, z)].SetFace(0);
		else
			blocks[index(x, y, z)].SetFace(5);
	}
}

//void	VertexCreator::faceCheck() {

//}

std::vector<float>	VertexCreator::getVertex() {
	return this->triangles;
}