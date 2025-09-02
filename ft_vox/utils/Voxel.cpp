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

std::vector<Vertex>	Voxel::GetVertex() {
	std::vector<Vertex> ret;
	ret.push_back(face[0].a);
	ret.push_back(face[0].b);
	ret.push_back(face[0].c);
	ret.push_back(face[0].d);
	ret.push_back(face[0].b);
	ret.push_back(face[0].c);
	
	ret.push_back(face[1].a);
	ret.push_back(face[1].b);
	ret.push_back(face[1].c);
	ret.push_back(face[1].d);
	ret.push_back(face[1].b);
	ret.push_back(face[1].c);
	
	ret.push_back(face[2].a);
	ret.push_back(face[2].b);
	ret.push_back(face[2].c);
	ret.push_back(face[2].d);
	ret.push_back(face[2].b);
	ret.push_back(face[2].c);
	
	ret.push_back(face[3].a);
	ret.push_back(face[3].b);
	ret.push_back(face[3].c);
	ret.push_back(face[3].d);
	ret.push_back(face[3].b);
	ret.push_back(face[3].c);
	
	ret.push_back(face[4].a);
	ret.push_back(face[4].b);
	ret.push_back(face[4].c);
	ret.push_back(face[4].d);
	ret.push_back(face[4].b);
	ret.push_back(face[4].c);
	
	ret.push_back(face[5].a);
	ret.push_back(face[5].b);
	ret.push_back(face[5].c);
	ret.push_back(face[5].d);
	ret.push_back(face[5].b);
	ret.push_back(face[5].c);
	return ret;
}

uint8_t	Voxel::GetFace(uint8_t n) {
	return vis.GetBool(n);
}

uint8_t	Voxel::GetTrasparence() {
	if (vis.GetBool(6) || vis.GetValue() == 192)
		return 1;
	return 0;
}

void	Voxel::calculateTriangle(float x, float y, float z) {
	Vertex	one, two, three1, three2;

	three1 = {x, y, z, 0, 0};
	three2 = {three1.x + 1, three1.y + 1, three1.z, 0, 0};
	two = {three1.x, three1.y + 1, three1.z, 0, 0};
	one = {three1.x + 1, three1.y, three1.z, 0, 0};
	face[0].a = one;
	face[0].b = three1;
	face[0].c = three2;
	face[0].d = two;
	setUV(0);
	three2 = {x + 1, y + 1, z + 1, 0, 0};
	three1 = {x, y, three2.z, 0, 0};
	one = {three2.x, y, three2.z, 0, 0};
	two = {x, three2.y, three2.z, 0, 0};
	face[1].a = one;
	face[1].b = three1;
	face[1].c = three2;
	face[1].d = two;
	setUV(1);
	one = {x, y, z, 0, 0};
	two = {one.x + 1, one.y, one.z + 1, 0, 0};
	three1 = {one.x, one.y, one.z + 1, 0, 0};
	three2 = {one.x + 1, one.y, one.z, 0, 0};
	face[2].a = one;
	face[2].b = three1;
	face[2].c = three2;
	face[2].d = two;
	setUV(2);
	one = {x + 1, y + 1, z + 1, 0, 0};
	two = {x, one.y, z, 0, 0};
	three1 = {one.x, one.y, z, 0, 0};
	three2 = {x, one.y, one.z, 0, 0};
	face[3].a = one;
	face[3].b = three1;
	face[3].c = three2;
	face[3].d = two;
	setUV(3);
	three2 = {x + 1, y + 1, z + 1, 0, 0};
	three1 = {three2.x, y, z, 0, 0};
	one = {three2.x, y, three2.z, 0, 0};
	two = {three2.x, three2.y, z, 0, 0};
	face[4].a = one;
	face[4].b = three1;
	face[4].c = three2;
	face[4].d = two;
	setUV(4);
	three1 = {x, y, z, 0, 0};
	three2 = {three1.x, three1.y + 1, three1.z + 1, 0, 0};
	two = {three1.x, three1.y + 1, three1.z, 0, 0};
	one = {three1.x, three1.y, three1.z + 1, 0, 0};
	face[5].a = one;
	face[5].b = three1;
	face[5].c = three2;
	face[5].d = two;
	setUV(5);
}

void	Voxel::SetFace(uint8_t n) {
	vis.SetBool(n);
}

void	Voxel::SetTrasparence() {
	vis.SetBool(6);
}

void	Voxel::setUV(int Face) {
	face[Face].a.u = texture[Face].u * Xtex;
	face[Face].a.v = texture[Face].v * Ytex;
	face[Face].d.u = (texture[Face].u + 1) * Xtex;
	face[Face].d.v = (texture[Face].v + 1) * Ytex;
	face[Face].b.u = (texture[Face].u + 1) * Xtex;
	face[Face].b.v = texture[Face].v * Ytex;
	face[Face].c.u = texture[Face].u * Xtex;
	face[Face].c.v = (texture[Face].v + 1) * Ytex;
}

std::ostream& operator<<(std::ostream& out, Voxel &rhs)
{
	if (rhs.GetTrasparence())
		out << "o";
	else
		out << "i";
	return out;
}