#include "headers/inclusion.h"
#include "WorldGenerator.hpp"
#include "headers/colors.h"
#include "Rendering.hpp"
#include "Player.hpp"

void takeTriangol(std::vector<Voxel> &blocks, std::vector<float> &ret);

int main (int ac, char **av) {
	(void)av;
	if (ac != 3)
		return -1;
	try {
		WorldGenerator	Notch(av[1], av[2]);
		GLFWwindow*		window;
		Rendering		Micol(800, 600);
		Player			Fre007("Fre007");

		window = Micol.Init("Minecraft");
		Micol.loadShaders("shader/vertex.glsl", "shader/fragment.glsl");
		Micol.loadTexture("texture/texture_clean.jpg");
		Micol.setupMouseControl();

		std::vector<Voxel>  temp;
		std::vector<float>	triangol;
		temp = Notch.Creation(0, 0);
		takeTriangol(temp, triangol);
		temp = Notch.Creation(16, 0);
		takeTriangol(temp, triangol);
		temp = Notch.Creation(-16, 0);
		takeTriangol(temp, triangol);
		temp = Notch.Creation(0, 16);
		takeTriangol(temp, triangol);
		temp = Notch.Creation(16, 16);
		takeTriangol(temp, triangol);
		temp = Notch.Creation(-16, 16);
		takeTriangol(temp, triangol);
		temp = Notch.Creation(0, -16);
		takeTriangol(temp, triangol);
		temp = Notch.Creation(16, -16);
		takeTriangol(temp, triangol);
		temp = Notch.Creation(-16, -16);
		takeTriangol(temp, triangol);

		Fre007.printPlayerInfo();
		while (!glfwWindowShouldClose(window)) {
			Micol.Loop(triangol);
			if (Fre007.changePosition(Micol.camera)) {
				Fre007.printPlayerInfo();
				Fre007.newChunck(Notch, triangol);
			}
		}
	} catch (const std::exception& e) {
		std::cerr << RED << "Error in " << e.what() << RESET << std::endl;
	}
}

//935890145