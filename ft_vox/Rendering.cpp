#include "Rendering.hpp"

Rendering::Rendering(int width, int height) {
	this->width = width;
	this->height = height;
	this->camera = {0, 0, 10};
}

Rendering::~Rendering() {}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	(void)window;
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
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void	Rendering::Loop() {
	while (!glfwWindowShouldClose(window)) {
		this->processInput();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);

		mat4 view;
		view.view(-camera.x, -camera.y, -camera.z);
	
		mat4 projection;
		projection.project(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	
		
		mat4 rotY, rotX;
		rotY.world("y", -this->rotY);
		rotX.world("x", -this->rotX);
		mat4 model = rotY.multiply(rotX);
	
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, view.data);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, projection.data);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, model.data);
	
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, triangles.size() * sizeof(float), triangles.data());
		int vertexCount = triangles.size() / 5;
		
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void	Rendering::setTriangles(std::vector<float>	input) {
	this->triangles = input;
}

//===============================
//= SHADERS AND TEXTURE LOADING =
//===============================

void Rendering::loadTexture(const std::string& texturePath) {
	stbi_set_flip_vertically_on_load(true); // Perché OpenGL legge dal basso

	int nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &texWidth, &texHeight, &nrChannels, 0);
	if (!data) {
		std::cerr << "Failed to load texture: " << texturePath  << "\n" << "Reason: " << stbi_failure_reason() << std::endl;
		return;
	}

    GLenum format = GL_RGB;
    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;

    glGenTextures(1, &texture); // Assicurati di generare la texture una sola volta
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

std::string	readShaderFile(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file)
		throw std::runtime_error("Cannot open shader file: " + filepath);
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint	compileShader(GLenum type, const std::string& source) {
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

void	Rendering::loadShaders(const char* vertexPath, const char* fragmentPath) {
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
	
	this->shaderProgram = program;
	glUseProgram(shaderProgram);
}

//===============================
//= MOUSE AND KEYBOARD CALLBACK =
//===============================

void Rendering::setupMouseControl() {
	// Nasconde il cursore e lo blocca nella finestra
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Salva il this per accedere dentro le lambda
	glfwSetWindowUserPointer(window, this);

	// Callback movimento mouse
	glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
		Rendering* r = static_cast<Rendering*>(glfwGetWindowUserPointer(win));
		if (r) r->mouse_callback(xpos, ypos);
	});
}

void Rendering::processInput() {
	// Chiudi finestra con ESC
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	const float speed = 0.1f;

	// Vettore direzione frontale (forward)
	float frontX = cos(rotX) * sin(rotY);
	float frontY = sin(rotX);
	float frontZ = cos(rotX) * cos(rotY);

	// Normalizza
	float length = sqrt(frontX * frontX + frontY * frontY + frontZ * frontZ);
	frontX /= length;
	frontY /= length;
	frontZ /= length;

	// Vettore laterale (right)
	float rightX = sin(rotY - 3.14f / 2.0f);
	float rightZ = cos(rotY - 3.14f / 2.0f);
	length = sqrt(rightX * rightX + rightZ * rightZ);
	rightX /= length;
	rightZ /= length;

	// Movimento
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.x += frontX * speed;
		camera.y += frontY * speed;
		camera.z += frontZ * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.x -= frontX * speed;
		camera.y -= frontY * speed;
		camera.z -= frontZ * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.x -= rightX * speed;
		camera.z -= rightZ * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.x += rightX * speed;
		camera.z += rightZ * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.y += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.y -= speed;
	}
}

void Rendering::mouse_callback(double xpos, double ypos) {
	(void)window;

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // invertito: più in alto = più positivo

	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.002f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	rotY += xoffset;
	rotX += yoffset;

	// Clamp della rotazione verticale (pitch)
	const float pitchLimit = 1.55f; // circa 89° in radianti
	if (rotX > pitchLimit)
		rotX = pitchLimit;
	if (rotX < -pitchLimit)
		rotX = -pitchLimit;
}