#pragma once

# include "headers/inclusion.h"

class Rendering {
private:
	std::vector<float>	triangles;
	unsigned int VAO, VBO;
	GLFWwindow* window;
	int	width, height;

public:
	Rendering(int width, int height);
	~Rendering();

	void	Init(std::string title);
	void	Loop();
	void	setTriangles(std::vector<float>	input);

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