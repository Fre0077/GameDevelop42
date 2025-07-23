#ifndef UTILS_H
#define UTILS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdint>

class mat4;
class rendering;

struct Vertex {
	float x, y, z;
	float u, v;
};

std::vector<float> readObjectFile (std::string filename);
std::vector<int> readFace(const std::string& str);
GLFWwindow* initOpenGL();
GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
void setupMouseControl(GLFWwindow* window, rendering* render);
void processInput(GLFWwindow* window, rendering* render);

