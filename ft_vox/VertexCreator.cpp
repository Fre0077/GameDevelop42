#include "VertexCreator.hpp"

VertexCreator::VertexCreator() {}

VertexCreator::~VertexCreator() {}

void	VertexCreator::calculateTriangle() {
	Vertex	one, two, three1, three2;
	long	size = blocks.size();
	Pos		zero;

	//std::cout << size << std::endl;
	for (int i = 0; i < size; i++) {
		zero = blocks[i].GetVoxel();
		if (blocks[i].GetFace(0)) {
			one = {zero.x, zero.y, zero.z, 0, 0};
			two = {one.x + 1, one.y + 1, one.z, 0, 0};
			three1 = {one.x, one.y + 1, one.z, 0, 0};
			three2 = {one.x + 1, one.y, one.z, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[i], 0);
		} else if (blocks[i].GetFace(5)) {
			one = {zero.x + 1, zero.y + 1, zero.z + 1, 0, 0};
			two = {one.x - 1, one.y - 1, one.z, 0, 0};
			three1 = {one.x, one.y - 1, one.z, 0, 0};
			three2 = {one.x - 1, one.y, one.z, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[i], 5);
		}
		if (blocks[i].GetFace(1)) {
			one = {zero.x, zero.y, zero.z, 0, 0};
			two = {one.x + 1, one.y, one.z + 1, 0, 0};
			three1 = {one.x, one.y, one.z + 1, 0, 0};
			three2 = {one.x + 1, one.y, one.z, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[i], 1);
		} else if (blocks[i].GetFace(3)) {
			one = {zero.x + 1, zero.y + 1, zero.z + 1, 0, 0};
			two = {one.x - 1, one.y - 1, one.z, 0, 0};
			three1 = {one.x, one.y, one.z - 1, 0, 0};
			three2 = {one.x - 1, one.y, one.z, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[i], 3);
		}
		if (blocks[i].GetFace(2)) {
			one = {zero.x + 1, zero.y + 1, zero.z + 1, 0, 0};
			two = {one.x - 1, one.y - 1, one.z, 0, 0};
			three1 = {one.x, one.y - 1, one.z, 0, 0};
			three2 = {one.x, one.y, one.z - 1, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[i], 2);
		} else if (blocks[i].GetFace(4)) {
			one = {zero.x, zero.y, zero.z, 0, 0};
			two = {one.x, one.y + 1, one.z + 1, 0, 0};
			three1 = {one.x, one.y + 1, one.z, 0, 0};
			three2 = {one.x, one.y, one.z + 1, 0, 0};
			texture.setUV(one, two, three1, three2, blocks[i], 4);
		}
		pushVertex(one, triangles);
		pushVertex(two, triangles);
		pushVertex(three1, triangles);
		pushVertex(three1, triangles);
	}
}

void	VertexCreator::setBlocks(std::vector<Voxel> &input) {
	this->blocks = input;
}

//void	VertexCreator::fovCheck() {
	
//}

void	VertexCreator::airCheck() {
	long	size = blocks.size();
	for (int i = 0; i < size; i++) {
		if (blocks[i].GetTrasparence()) {
			blocks.erase(blocks.begin() + i);
			continue;
		}
	}
}

void	VertexCreator::directionCheck(float x, float y, float z) {
	long	size = blocks.size();
	for (int i = 0; i < size; i++) {
		if (blocks[i].GetVoxel().x < x)
			blocks[i].SetFace(4);
		else
			blocks[i].SetFace(2);
		if (blocks[i].GetVoxel().y < y)
			blocks[i].SetFace(1);
		else
			blocks[i].SetFace(3);
		if (blocks[i].GetVoxel().z < z)
			blocks[i].SetFace(0);
		else
			blocks[i].SetFace(5);
	}
}

//void	VertexCreator::faceCheck() {

//}

std::vector<float>	VertexCreator::getVertex() {
	return this->triangles;
}