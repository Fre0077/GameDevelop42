#include "rendering.hpp"
#include "mat4.hpp"

rendering::rendering(GLuint shaderProgram) {
    lastX = 400.0f;
	lastY = 300.0f;
	rotX = 0.0f;
	rotY = 0.0f;
	firstMouse = true;
	leftMousePressed = false;
	textureLoaded = false;
	textureOn = false;

	cameraPos = glm::vec3(0.0f, 1.0f, 8.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenTextures(1, &texture);

	glGenTextures(1, &whiteTexture);
	glBindTexture(GL_TEXTURE_2D, whiteTexture);
	unsigned char whitePixel[3] = {255, 255, 255};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, whitePixel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	this->shaderProgram = shaderProgram;
	glUseProgram(shaderProgram);
}

rendering::~rendering() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &whiteTexture);
}

void rendering::renderTriangles(const std::vector<float>& triangles) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 view;
	view.view(-cameraPos.x, -cameraPos.y, -cameraPos.z);

	mat4 projection;
	projection.project(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

	mat4 rotY, rotX;
	rotY.world("y", this->rotY);
	rotX.world("x", this->rotX);
	mat4 model = rotY.multiply(rotX);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, view.data);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, projection.data);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, model.data);

	glBufferData(GL_ARRAY_BUFFER, triangles.size() * sizeof(float), triangles.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	int vertexCount = triangles.size() / 8;
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void rendering::useTexture() {
	textureOn = !textureOn;
	glUniform1i(glGetUniformLocation(shaderProgram, "useTexture"), textureOn && textureLoaded);
	if (textureOn && textureLoaded) {
		glBindTexture(GL_TEXTURE_2D, texture);
	} else {
		glBindTexture(GL_TEXTURE_2D, whiteTexture);
	}
}

void rendering::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
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

	rotY += xoffset;
	rotX += yoffset;
}

void rendering::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
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

void rendering::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	(void) window;
	(void) xoffset;
	
	cameraPos.z -= (float)yoffset * 0.3f;
	
	if (cameraPos.z < 0.5f)
		cameraPos.z = 0.5f;
	if (cameraPos.z > 10.0f)
		cameraPos.z = 10.0f;
}

//================
//Support function
//================

unsigned char* readBMP(const std::string& filename, int& width, int& height) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		std::cout << "Cannot open BMP file: " << filename << std::endl;
		return nullptr;
	}

	char signature[2];
	file.read(signature, 2);
	if (!file) {
		std::cout << "Error reading file signature" << std::endl;
		return nullptr;
	}

	if (signature[0] != 'B' || signature[1] != 'M') {
		std::cout << "Not a valid BMP file - signature mismatch" << std::endl;
		return nullptr;
	}

	BMPHeader header;
	header.signature[0] = signature[0];
	header.signature[1] = signature[1];
	
	file.read(reinterpret_cast<char*>(&header.fileSize), sizeof(BMPHeader) - 2);
	if (!file) {
		std::cout << "Error reading BMP header" << std::endl;
		return nullptr;
	}

	if (header.bitsPerPixel != 24 || header.compression != 0) {
		std::cout << "Only 24-bit uncompressed BMP supported" << std::endl;
		return nullptr;
	}

	width = header.width;
	height = header.height;

	int padding = (4 - (width * 3) % 4) % 4;

	unsigned char* imageData = new unsigned char[width * height * 3];

	file.seekg(header.dataOffset);
	if (!file) {
		std::cout << "Error seeking to data offset" << std::endl;
		delete[] imageData;
		return nullptr;
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			unsigned char pixel[3];
			file.read(reinterpret_cast<char*>(pixel), 3);
			if (!file) {
				std::cout << "Error reading pixel data at row " << y << ", col " << x << std::endl;
				delete[] imageData;
				return nullptr;
			}
			int index = (y * width + x) * 3;
			imageData[index] = pixel[2];
			imageData[index + 1] = pixel[1];
			imageData[index + 2] = pixel[0];
		}
		file.seekg(padding, std::ios::cur);
	}

	file.close();
	std::cout << "BMP loaded successfully!" << std::endl;
	return imageData;
}

bool rendering::loadTexture(const std::string& texturePath) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height;
	unsigned char* data = readBMP(texturePath, width, height);
	
	if (data) {
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		delete[] data;
		textureLoaded = true;
		std::cout << "BMP texture loaded successfully: " << texturePath << std::endl;
		return true;
	}
	std::cout << "Failed to load BMP texture: " << texturePath << std::endl;
	return false;
}
