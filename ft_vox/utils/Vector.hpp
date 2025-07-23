#pragma once

# include "../headers/inclusion.h"

class Vector {
private:
	float x, y;
public:
	Vector(float x, float y);
	~Vector();

	float	getX();
	float	getY();
	float	prod(Vector vex);
};
