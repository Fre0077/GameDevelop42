#include "mat4.hpp"

mat4::mat4() {
	for (int i = 0; i < 15; i++)
		this->data[i] = 0.0f;
	this->data[0] = this->data[5] = this->data[10] = this->data[15] = 1.0f;
}

mat4::~mat4() {}

void	mat4::world(std::string ax, float angle) {
	if (ax == "x") {
		this->data[5] = cos(angle);
		this->data[6] = -sin(angle);
		this->data[9] = sin(angle);
		this->data[10] = cos(angle);
	} else if (ax == "y") {
		this->data[0] = cos(angle);
		this->data[2] = sin(angle);
		this->data[8] = -sin(angle);
		this->data[10] = cos(angle);
	} else if (ax == "z") {
		this->data[0] = cos(angle);
		this->data[1] = -sin(angle);
		this->data[4] = sin(angle);
		this->data[5] = cos(angle);
	}
}

void	mat4::world(float x, float y, float z) {
	this->data[12] = x;
	this->data[13] = y;
	this->data[14] = z;
}

void	mat4::view(std::string ax, float angle) {
	this->world(ax, angle);
}

void	mat4::view(float x, float y, float z) {
	this->world(x, y, z);
}

void	mat4::project(float fov, float aspect, float near, float far) {
	for (int i = 0; i < 16; i++)
		this->data[i] = 0.0f;

	float fov_rad = fov * 3.14159265359f / 180.0f;
	float f = 1.0f / tan(fov_rad / 2.0f);

	this->data[0] = f / aspect;
	this->data[5] = f;
	this->data[10] = -(far + near) / (far - near);
	this->data[14] = -2.0f * far * near / (far - near);
	this->data[11] = -1.0f;
}

mat4	mat4::multiply(const mat4& other) const {
	mat4 result;
	for (int i = 0; i < 16; i++)
		result.data[i] = 0.0f;

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			for (int k = 0; k < 4; k++) {
				result.data[col * 4 + row] += 
					this->data[k * 4 + row] * other.data[col * 4 + k];
			}
		}
	}
	
	return result;
}
