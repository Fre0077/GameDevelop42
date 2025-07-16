#include "../include/utils.h"
#include "../class/rendering.hpp"
#include <unistd.h>
#include <sys/stat.h>

int main (int ac, char** av) {
	if (ac != 2)
		return -1;
	try {
		std::string filename(av[1]);
		std::vector<float> triangles = readObjectFile(filename);

		GLFWwindow* window = initOpenGL();

		GLuint shaderProgram = loadShaders("shader/vertex.glsl", "shader/fragment.glsl");

		rendering *render = new rendering(shaderProgram);

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

		glDeleteProgram(shaderProgram);
		glfwDestroyWindow(window);
		glfwTerminate();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		glfwTerminate();
		return -1;
	}
	return 0;
}
