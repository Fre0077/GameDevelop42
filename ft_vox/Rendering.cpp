#include "Rendering.hpp"

Rendering::Rendering(int width, int height) {
	this->width = width;
	this->height = height;
}

Rendering::~Rendering() {}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void	Rendering::Init(std::string title) {
	if (!glfwInit()) {
		std::cerr << "Errore: impossibile inizializzare GLFW\n";
		throw InitProblem();
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(this->width, this->height, title.c_str(), NULL, NULL);
	if (!window) {
		std::cerr << "Errore: impossibile creare la finestra GLFW\n";
		glfwTerminate();
		throw ErrorWindow();
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Errore: GLEW non è riuscito a inizializzarsi\n";
		throw GlewError();
	}

	glViewport(0, 0, this->width, this->height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void	Rendering::Loop() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, triangles.size() * sizeof(float), triangles.data());

	glBindVertexArray(VAO);
	int vertexCount = triangles.size() / 5;
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void	Rendering::setTriangles(std::vector<float>	input) {
	this->triangles = input;
}
