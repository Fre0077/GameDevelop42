#pragma once

# include "headers/inclusion.h"
# include "headers/stb_image.h"
# include "utils/mat4.hpp"

class mat4;

class Rendering {
private:
	std::vector<float>	triangles;
	unsigned int		VAO, VBO;
	unsigned int		texture;
	GLFWwindow*			window;
	GLuint				shaderProgram;
	float				lastX, lastY;
	float				rotX, rotZ, rotY, saveX, saveZ;
	bool				firstMouse;
	int					texWidth, texHeight;
	int					width, height;
	Pos					camera;

	float	speed;
	bool	mouseButtonPressed = false;
public:
	Rendering(int width, int height);
	~Rendering();

	void	Init(std::string title);
	void	Loop();
	void	setTriangles(std::vector<float>	input);

	void	loadShaders(const char* vertexPath, const char* fragmentPath);
	void	loadTexture(const std::string& texturePath);

	void	mouse_callback(double xpos, double ypos);
	void	setupMouseControl();
	void	processInput();

	class ErrorWindow : public std::exception {
	public:
		const char* what() const noexcept override {
			return "Rendering: couldn't create the reqeust window";
		}
	};

	class InitProblem : public std::exception {
	public:
	const char* what() const noexcept override {
			return "Rendering: couldn't initialize opengl";
		}
	};

	class GlewError : public std::exception {
	public:
	const char* what() const noexcept override {
			return "Rendering: couldn't initialize GLEW";
		}
	};
};