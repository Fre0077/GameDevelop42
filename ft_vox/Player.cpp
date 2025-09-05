#include "Player.hpp"

Player::Player(std::string inputName) {
	this->coordinate = {0, 0, 0};
	this->chunck = {0, 0};
	this->name = inputName;
}

Player::~Player() {}

int	Player::changePosition(Pos &newPos) {
	int ret = 0;
	if (newPos.x < this->chunck.x) {
		this->chunck.x -= 16;
		ret = 1;
	} else if (Abs(newPos.x - this->chunck.x) > 16) {
		this->chunck.x += 16;
		ret = 2;
	}
	if (newPos.z < this->chunck.z) {
		this->chunck.z -= 16;
		ret = 3;
	} else if (Abs(newPos.z - this->chunck.z) > 16) {
		this->chunck.z += 16;
		ret = 4;
	}
	this->coordinate = newPos;
	return ret;
}

void takeTriangol(std::vector<Voxel> &blocks, std::vector<float> &ret) {
	int x = 0, y = -1, z = 0;
	while (cicle(x, y, z)) {
		const std::vector<Vertex> &vertices = blocks[index(x, y, z)].GetVertex();
		for (const Vertex &v : vertices) {
			ret.push_back(v.x);
			ret.push_back(v.y);
			ret.push_back(v.z);
			ret.push_back(v.u);
			ret.push_back(v.v);
		}
	}
}

void	Player::newChunck(WorldGenerator &Notch, std::vector<float> &triangol) {
	std::vector<Voxel>  temp;

	triangol.clear();
	temp = Notch.Creation(this->chunck.x, this->chunck.z);
	takeTriangol(temp, triangol);
	temp = Notch.Creation(this->chunck.x + 16, this->chunck.z);
	takeTriangol(temp, triangol);
	temp = Notch.Creation(this->chunck.x - 16, this->chunck.z);
	takeTriangol(temp, triangol);
	temp = Notch.Creation(this->chunck.x, this->chunck.z + 16);
	takeTriangol(temp, triangol);
	temp = Notch.Creation(this->chunck.x + 16, this->chunck.z + 16);
	takeTriangol(temp, triangol);
	temp = Notch.Creation(this->chunck.x - 16, this->chunck.z + 16);
	takeTriangol(temp, triangol);
	temp = Notch.Creation(this->chunck.x, this->chunck.z - 16);
	takeTriangol(temp, triangol);
	temp = Notch.Creation(this->chunck.x + 16, this->chunck.z - 16);
	takeTriangol(temp, triangol);
	temp = Notch.Creation(this->chunck.x - 16, this->chunck.z - 16);
	takeTriangol(temp, triangol);
}

void	Player::printPlayerInfo() {
	std::cout << "Chunck Info:" << std::endl;
	std::cout << "x:" << this->chunck.x << "\nz:" << this->chunck.z << std::endl;
	std::cout << "Player position Info:" << std::endl;
	std::cout << "x:" << this->coordinate.x << "\nz:" << this->coordinate.z << std::endl;
}