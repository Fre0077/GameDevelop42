#include "../include/utils.h"
#include "../class/mat4.hpp"
#include "../class/rendering.hpp"

//split
std::vector<int> readFace(const std::string& str) {
	std::vector<int> result;
	std::stringstream ss(str);
	std::string token;
	
	ss >> token;
	while (ss >> token) {
		int value = std::stoi(token);
		result.push_back(value - 1);
	}
	return result;
}

void	pushTriangle(std::vector<float> *triangol, const Vertex& v) {
	triangol->push_back(v.x);
	triangol->push_back(v.y);
	triangol->push_back(v.z);
	triangol->push_back(v.r);
	triangol->push_back(v.g);
	triangol->push_back(v.b);
}

// Legge .obj restituendo un vector di vector di float da usare per il VBO
std::vector<float> readObjectFile (std::string filename) {
	std::vector<float> triangols;
	std::ifstream file(filename);

	if (!file) throw std::runtime_error("Cannot open file: " + filename);
	
	std::string line;
	std::string dummy;
	std::vector<Vertex> vertices;
	while (std::getline(file, line)) {
		if (line[0] == 'v') {
			std::istringstream iss(line);
			Vertex vertex;

			if (vertices.size() % 2 == 0) {
				vertex.r = 0.9;
				vertex.g = 0.9;
				vertex.b = 0.8;
			} else {
				vertex.r = 0.4;
				vertex.g = 0.4;
				vertex.b = 0.4;
			}
			if (iss >> dummy >> vertex.x >> vertex.y >> vertex.z)
				vertices.push_back(vertex);
		} else if (line[0] == 'f') {
			std::vector<int> seg = readFace(line);
			if (seg.size() == 4){
				pushTriangle(&triangols, vertices[seg[0]]);
				pushTriangle(&triangols, vertices[seg[2]]);
				pushTriangle(&triangols, vertices[seg[3]]);
			}
			pushTriangle(&triangols, vertices[seg[0]]);
			pushTriangle(&triangols, vertices[seg[1]]);
			pushTriangle(&triangols, vertices[seg[2]]);
		}
	}
	return triangols;
}

//setta OpenGL e GLFW e GLEW
GLFWwindow* initOpenGL() {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW");
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);

	GLFWwindow* window = glfwCreateWindow(800, 600, "SCOP - Triangle Renderer", NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLEW");
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	return window;
}

// legge il file delle shader
std::string readShaderFile(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file) {
		throw std::runtime_error("Cannot open shader file: " + filepath);
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

// compila i file shader
GLuint compileShader(GLenum type, const std::string& source) {
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::string shaderType = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
		throw std::runtime_error("Shader compilation failed (" + shaderType + "): " + infoLog);
	}

	return shader;
}

//carica i file per la shader
GLuint loadShaders(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode = readShaderFile(vertexPath);
	std::string fragmentCode = readShaderFile(fragmentPath);

	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	return program;
}

// Setup del controllo del mouse
void setupMouseControl(GLFWwindow* window, rendering* render) {
	// Mostra il cursore (non più nascosto)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	
	// Salva il puntatore alla classe rendering per le callback
	glfwSetWindowUserPointer(window, render);
	
	// Registra le callback del mouse (devono essere funzioni statiche)
	glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
		rendering* r = static_cast<rendering*>(glfwGetWindowUserPointer(win));
		if (r) r->mouse_callback(win, xpos, ypos);
	});
	
	glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
		rendering* r = static_cast<rendering*>(glfwGetWindowUserPointer(win));
		if (r) r->mouse_button_callback(win, button, action, mods);
	});
	
	glfwSetScrollCallback(window, [](GLFWwindow* win, double xoffset, double yoffset) {
		rendering* r = static_cast<rendering*>(glfwGetWindowUserPointer(win));
		if (r) r->scroll_callback(win, xoffset, yoffset);
	});
}

//setta funzionalità dei tasti
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
