#include "VertexCreator.hpp"

VertexCreator::VertexCreator() {}

VertexCreator::~VertexCreator() {}

void	VertexCreator::calculateTriangle() {
	std::vector<std::vector<float>>	face;
	Vertex							one, two, three1, three2;
	float							x = 0, y = -1, z = 0;
	int								i;

	while (cicle(x, y, z)) {
		i = index(x, y, z);
		one = {x, y, z, 0, 0};
		two = {one.x + 1, one.y + 1, one.z, 0, 0};
		three1 = {one.x, one.y + 1, one.z, 0, 0};
		three2 = {one.x + 1, one.y, one.z, 0, 0};
		texture.setUV(one, two, three1, three2, blocks[i], 0);
		pushVertex(three1, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		pushVertex(three2, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		one = {x + 1, y + 1, z + 1, 0, 0};
		two = {x, y, one.z, 0, 0};
		three1 = {one.x, y, one.z, 0, 0};
		three2 = {x, one.y, one.z, 0, 0};
		texture.setUV(one, two, three1, three2, blocks[i], 5);
		pushVertex(three1, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		pushVertex(three2, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		one = {x, y, z, 0, 0};
		two = {one.x + 1, one.y, one.z + 1, 0, 0};
		three1 = {one.x, one.y, one.z + 1, 0, 0};
		three2 = {one.x + 1, one.y, one.z, 0, 0};
		texture.setUV(one, two, three1, three2, blocks[i], 1);
		pushVertex(three1, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		pushVertex(three2, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		one = {x + 1, y + 1, z + 1, 0, 0};
		two = {x, one.y, z, 0, 0};
		three1 = {one.x, one.y, z, 0, 0};
		three2 = {x, one.y, one.z, 0, 0};
		texture.setUV(one, two, three1, three2, blocks[i], 3);
		pushVertex(three1, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		pushVertex(three2, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		one = {x + 1, y + 1, z + 1, 0, 0};
		two = {one.x, y, z, 0, 0};
		three1 = {one.x, y, one.z, 0, 0};
		three2 = {one.x, one.y, z, 0, 0};
		texture.setUV(one, two, three1, three2, blocks[i], 2);
		pushVertex(three1, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		pushVertex(three2, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		one = {x, y, z, 0, 0};
		two = {one.x, one.y + 1, one.z + 1, 0, 0};
		three1 = {one.x, one.y + 1, one.z, 0, 0};
		three2 = {one.x, one.y, one.z + 1, 0, 0};
		texture.setUV(one, two, three1, three2, blocks[i], 4);
		pushVertex(three1, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
		pushVertex(three2, face[i]);
		pushVertex(one, face[i]);
		pushVertex(two, face[i]);
	}
	this->faces = face;
}

void	VertexCreator::setBlocks(std::vector<Voxel> &input) {
	this->blocks = input;
}

//void	VertexCreator::fovCheck() {
	
//}

void	VertexCreator::directionCheck(Pos input) {
	float	x = 0, y = -1, z = 0;

	while (cicle(x, y, z)) {
		if (x < input.x)
			blocks[index(x, y, z)].SetFace(4);
		else
			blocks[index(x, y, z)].SetFace(2);
		if (y < input.y)
			blocks[index(x, y, z)].SetFace(1);
		else
			blocks[index(x, y, z)].SetFace(3);
		if (z < input.z)
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