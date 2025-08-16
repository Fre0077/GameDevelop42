#include "headers/inclusion.h"
#include "WorldGenerator.hpp"
#include "headers/colors.h"
#include "Rendering.hpp"

std::vector<float>	takeTriangol(std::vector<Voxel> blocks);

int main (int ac, char **av) {
	(void)av;
	if (ac != 3)
		return -1;
	try {
		WorldGenerator	Notch(av[1], av[2]);
		Rendering		Micol(800, 600);
		GLFWwindow*		window;

		window = Micol.Init("Minecraft");
		Micol.loadShaders("shader/vertex.glsl", "shader/fragment.glsl");
		Micol.loadTexture("texture/texture_clean.jpg");
		Micol.setupMouseControl();

		std::vector<Voxel> temp = Notch.Creation(0, 0);

		std::vector<float>	triangol = takeTriangol(temp);

		while (!glfwWindowShouldClose(window)) {
			Micol.setTriangles(triangol);
			Micol.Loop();
		}
	} catch (const std::exception& e) {
		std::cerr << RED << "Error in " << e.what() << RESET << std::endl;
	}
}

std::vector<float> takeTriangol(std::vector<Voxel> blocks) {
    std::vector<float> ret;
    float x = 0, y = -1, z = 0;

    while (cicle(x, y, z)) {
        std::vector<Vertex> vertices = blocks[index(x, y, z)].GetVertex();
        for (const Vertex &v : vertices) {
            ret.push_back(v.x);
            ret.push_back(v.y);
            ret.push_back(v.z);
            ret.push_back(v.u);
            ret.push_back(v.v);
        }
    }

    return ret;
}

//935890145