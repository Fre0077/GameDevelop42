#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../include/utils.h"

struct BMPHeader {
    char signature[2];
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
    uint32_t headerSize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t xResolution;
    uint32_t yResolution;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};

class mat4;

class rendering {
	private:
		float startSmooth;
		float textureSmooth;
		float rotX , rotY;
		float lastX, lastY;
		bool firstMouse;
		bool witchSmooth;
		bool textureLoaded;
		bool leftMousePressed;
		glm::vec3 cameraUp;
		glm::vec3 cameraPos;
		glm::vec3 cameraTarget;
		GLuint texture;
		GLuint VAO, VBO;
		GLuint whiteTexture;
		GLuint shaderProgram;
	public:
		~rendering();
		rendering(GLuint shaderProgram);

		bool	loadTexture(const std::string& texturePath);

		void	useTexture();
		void	smoothCriminal();
		void	createDefaultTexture();
		void	centerObj(std::vector<float>& triangles);
		void	renderTriangles(const std::vector<float>& triangles);
		void	mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void	scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		void	mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

#endif
