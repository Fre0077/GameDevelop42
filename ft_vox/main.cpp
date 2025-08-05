#include "headers/inclusion.h"
#include "WorldGenerator.hpp"
#include "VertexCreator.hpp"
#include "headers/colors.h"
#include "Rendering.hpp"

//int main() {
//	try {
//		Rendering Micol(1920, 1080);
//		Micol.Init("Simple Triangle");
//		Micol.loadShaders("shader/vertex.glsl", "shader/fragment.glsl");
//		Micol.loadTexture("texture/texture_clean.jpg");
//		Micol.setupMouseControl();

//		float X = 6;
//		float Y = 5;
//		std::vector<float> triangle = {
//			-0.5f,  0.5f, 0.0f, Xtex * X, Ytex * (Y + 1),  // Top Left
//			-0.5f, -0.5f, 0.0f, Xtex * X, Ytex * Y,  // Bottom Left
//			0.5f,  0.5f, 0.0f, Xtex * (X + 1), Ytex * (Y + 1),  // Top Right
//			-0.5f, -0.5f, 0.0f, Xtex * X, Ytex * Y,  // Bottom Left
//			0.5f, -0.5f, 0.0f, Xtex * (X + 1), Ytex * Y,  // Bottom Right
//			0.5f,  0.5f, 0.0f, Xtex * (X + 1), Ytex * (Y + 1)   // Top Right
//		};


//		Micol.setTriangles(triangle);
//		Micol.Loop();
//	} catch (const std::exception& e) {
//		std::cerr << "Errore: " << e.what() << std::endl;
//		return 1;
//	}
//	return 0;
//}

int main (int ac, char **av) {
	(void)av;
	if (ac != 3)
		return -1;
	try {
		WorldGenerator	Notch(av[1], av[2]);
		VertexCreator	Karen;
		Rendering		Micol(800, 600);

		Micol.Init("Minecraft");
		Micol.loadShaders("shader/vertex.glsl", "shader/fragment.glsl");
		Micol.loadTexture("texture/texture_clean.jpg");
		Micol.setupMouseControl();
		std::vector<Voxel> temp = Notch.Creation(0, 0);
		Karen.setBlocks(temp);
		Karen.calculateTriangle();
		std::vector<float> block = Karen.getVertex();
		Micol.setTriangles(block);
		Micol.Loop();
	} catch (const std::exception& e) {
		std::cerr << RED << "Error in " << e.what() << RESET << std::endl;
	}
}

//935890145