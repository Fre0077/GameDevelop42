#include "../include/utils.h"
#include "../class/rendering.hpp"
#include <unistd.h>
#include <sys/stat.h>

int main (int ac, char** av) {
	if (ac != 2)
		return -1;
	GLFWwindow* window = nullptr;
    GLuint shaderProgram = 0;
    rendering* render = nullptr;
	try {
		std::string filename(av[1]);
		std::vector<float> triangles = readObjectFile(filename);

		window = initOpenGL();
		shaderProgram = loadShaders("shader/vertex.glsl", "shader/fragment.glsl");
		render = new rendering(shaderProgram);

		if (!render->loadTexture("myLittleShit.bmp")) {
			std::cout << "Warning: Could not load texture, using colors only" << std::endl;
		}
		
		setupMouseControl(window, render);

		while (!glfwWindowShouldClose(window)) {
			processInput(window, render);

            render->renderTriangles(triangles);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

		delete render;
		glDeleteProgram(shaderProgram);
		glfwDestroyWindow(window);
		glfwTerminate();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		if (render) delete render;
		if (shaderProgram) glDeleteProgram(shaderProgram);
		if (window) glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}
	return 0;
}
