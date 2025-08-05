#pragma once

# include <sys/types.h>
# include <sys/stat.h>
# include <algorithm>
# include <exception>
# include <stdexcept>
# include <iostream>
# include <dirent.h>
# include <iomanip>
# include <stdio.h>
# include <cstdint>
# include <fstream>
# include <cstdint>
# include <errno.h>
# include <cstring>
# include <cstdlib>
# include <sstream>
# include <cstdint>
# include <vector>
# include <string>
# include <cerrno>
# include <cmath>

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

# include "stb_image.h"

# define Ytex 0.03125f
# define Xtex 0.015625f

#define P 3.14159265358979323846f

struct Vertex {
	float x, y, z, u, v;
};

struct Pos {
	float x, y, z;
};

struct tex {
	uint8_t u, v;
};

void	pushVertex(Vertex &ver, std::vector<float> &vec);
void	printVecF(const std::vector<float>& vec);
void	printVec(const std::vector<float>& vec);