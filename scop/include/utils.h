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
#include "../class/mat4.hpp"

struct Vertex {
    float x, y, z;
    float r, g, b;
};

std::vector<std::vector<float>> readObjectFile (std::string filename);
GLFWwindow* initOpenGL();
GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
void renderTriangles(const std::vector<std::vector<float>>& triangles, GLuint shaderProgram);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void setupMouseControl(GLFWwindow* window);
void processInput(GLFWwindow* window);
