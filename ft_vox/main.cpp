#include "headers/inclusion.h"
#include "WorldGenerator.hpp"
#include "headers/colors.h"
#include "Rendering.hpp"

std::vector<float> takeTriangol(std::vector<Voxel> &blocks);

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

		//Voxel	JustOne;
		//Texture	texture;
		//texture.stone(JustOne);
		//JustOne.calculateTriangle(0, 0, 0);
		//std::vector<float>	triangol;
		//std::vector<Vertex> vertices = JustOne.GetVertex();
		//for (const Vertex &v : vertices) {
		//	triangol.push_back(v.x);
        //    triangol.push_back(v.y);
        //    triangol.push_back(v.z);
        //    triangol.push_back(v.u);
        //    triangol.push_back(v.v);
        //}
		
		std::vector<Voxel> temp = Notch.Creation(0, 0);
		std::vector<float>	triangol = takeTriangol(temp);
		
		while (!glfwWindowShouldClose(window)) {
			Micol.Loop(triangol);
		}
	} catch (const std::exception& e) {
		std::cerr << RED << "Error in " << e.what() << RESET << std::endl;
	}
}

std::vector<float> takeTriangol(std::vector<Voxel> &blocks) {
	std::vector<float> ret;

	int x = 0, y = -1, z = 0;
	while (cicle(x, y, z)) {
		Voxel &voxel = blocks[index(x, y, z)];
		if (!voxel.GetTrasparence())
			continue;
		const std::vector<Vertex> &vertices = voxel.GetVertex();
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