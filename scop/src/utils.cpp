#include "../include/utils.h"
#include "../class/mat4.hpp"

// Variabili globali per il controllo della rotazione dell'oggetto
float lastX = 400.0f, lastY = 300.0f;  // Centro dello schermo
float objectRotationX = 0.0f;  // Rotazione dell'oggetto sull'asse X
float objectRotationY = 0.0f;  // Rotazione dell'oggetto sull'asse Y
bool firstMouse = true;
bool leftMousePressed = false;

// Camera fissa
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);  // Camera fissa davanti all'oggetto
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);  // Guarda l'origine
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // Vettore "su"

// Legge .obj restituendo un vector di vector di lfoat da usare per il VBO
std::vector<std::vector<float>> readObjectFile (std::string filename) {
	std::vector<std::vector<float>> triangols;
	std::ifstream file(filename);

	if (!file) {
		throw std::runtime_error("Cannot open file: " + filename);
	}
	
	std::string line;
	std::vector<Vertex> vertices;
	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#' || line[0] != 'v') continue;
		std::istringstream iss(line);
		Vertex vertex;
		std::string dummy;
		
		if (iss >> dummy >> vertex.x >> vertex.y >> vertex.z >> vertex.r >> vertex.g >> vertex.b)
			vertices.push_back(vertex);

		if (vertices.size() == 3) {
			std::vector<float> triangol;
			for (int i = 0; i < 3; i++) {
				const Vertex& v = vertices[i];
				triangol.push_back(v.x);
				triangol.push_back(v.y);
				triangol.push_back(v.z);
				triangol.push_back(v.r);
				triangol.push_back(v.g);
				triangol.push_back(v.b);
			}
			triangols.push_back(triangol);
			vertices.clear();
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

std::string readShaderFile(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file) {
		throw std::runtime_error("Cannot open shader file: " + filepath);
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

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







//render di tutti i triangoli presenti nel file
void renderTriangles(const std::vector<std::vector<float>>& triangles, GLuint shaderProgram) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram);

	mat4 view;
	view.view(-cameraPos.x, -cameraPos.y, -cameraPos.z);

	mat4 projection;
	projection.project(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

	mat4 rotY, rotX;
	rotY.world("y", objectRotationY);
	rotX.world("x", objectRotationX);
	mat4 model = rotY.multiply(rotX);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, view.data);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, projection.data);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, model.data);

	for (const auto& triangle : triangles) {
		GLuint VAO, VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, triangle.size() * sizeof(float), triangle.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
}

// Callback del mouse per il controllo della rotazione dell'oggetto
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	(void) window;

	if (!leftMousePressed) {
		firstMouse = true;
		return;
	}

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = lastX - xpos;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.01f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	objectRotationY += xoffset;
	objectRotationX += yoffset;
}

// Callback per i click del mouse
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	(void) window;
	(void) mods;
	
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			leftMousePressed = true;
		} else if (action == GLFW_RELEASE) {
			leftMousePressed = false;
		}
	}
}

// Callback per la rotella del mouse (zoom tramite spostamento camera)
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	(void) window;
	(void) xoffset;
	
	cameraPos.z -= (float)yoffset * 0.3f;
	
	if (cameraPos.z < 0.5f)
		cameraPos.z = 0.5f;
	if (cameraPos.z > 10.0f)
		cameraPos.z = 10.0f;
}

// Setup del controllo del mouse
void setupMouseControl(GLFWwindow* window) {
	// Mostra il cursore (non più nascosto)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	
	// Registra le callback del mouse
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
