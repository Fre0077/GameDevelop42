#include "Vector.hpp"

Vector::Vector(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector::~Vector() {}

float	Vector::prod(Vector vex) {
	return ((this->x * vex.x) + (this->y * vex.y));
}

float	Vector::getX() {
	return this->x;
}

float	Vector::getY() {
	return this->y;
}