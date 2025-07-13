#include "../include/utils.h"

int main (int ac, char** av) {
	if (ac != 2)
		return -1;
	try {
		std::string filename(av[1]);
		std::vector<std::vector<float>> triangles = readObjectFile(filename);

		GLFWwindow* window = initOpenGL();

		setupMouseControl(window);

		GLuint shaderProgram = loadShaders("shader/vertex.glsl", "shader/fragment.glsl");

		while (!glfwWindowShouldClose(window)) {
			// Processa input da tastiera
			processInput(window);
			
			// Renderizza la scena
            renderTriangles(triangles, shaderProgram);
            
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
