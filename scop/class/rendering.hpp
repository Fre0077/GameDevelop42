#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

// Forward declaration
class mat4;

class rendering {
	private:
		float lastX, lastY;
		float rotX , rotY ;
		bool firstMouse;
		bool leftMousePressed;
		glm::vec3 cameraPos;
		glm::vec3 cameraTarget;
		glm::vec3 cameraUp;
		GLuint VAO, VBO;
	public:
		rendering();
		~rendering();
		void renderTriangles(const std::vector<float>& triangles, GLuint shaderProgram);
		void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif
