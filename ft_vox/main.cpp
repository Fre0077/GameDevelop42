#include "headers/inclusion.h"
#include "WorldGenerator.hpp"
#include "VertexCreator.hpp"
#include "headers/colors.h"
#include "Rendering.hpp"

int main() {
	try {
		Rendering Micol(800, 600);
		Micol.Init("Simple Triangle");
		Micol.loadShaders("shader/vertex.glsl", "shader/fragment.glsl");
		Micol.loadTexture("texture/texture_clean.jpg");

		std::vector<float> triangle = {
			// Vertici 3D        // Texture coords
			 0.0f,  0.5f, 0.0f,   13.5f * 1.0f / 64.0f, 1.0f * 14.0f / 32.0f, // Top
			-0.5f, -0.5f, 0.0f,   13.0f * 1.0f / 64.0f, 0.0f * 14.0f / 32.0f, // Bottom left
			 0.5f, -0.5f, 0.0f,   14.0f * 1.0f / 64.0f, 0.0f * 14.0f / 32.0f  // Bottom right
		};

		Micol.setTriangles(triangle);
		Micol.Loop();
	} catch (const std::exception& e) {
		std::cerr << "Errore: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}

//int main (int ac, char **av) {
//	(void)av;
//	if (ac != 3)
//		return -1;
//	try {
//		WorldGenerator	Notch(av[1], av[2]);
//		VertexCreator	Karen;
//		Rendering		Micol(1920, 1080);

//		Micol.Init("Minecraft");
//		Micol.loadShaders("shader/vertex.glsl", "shader/fragment.glsl");
//		Micol.loadTexture("texture/texture_clean.jpg");
//		Micol.setupMouseControl();
//		std::vector<Voxel> temp = Notch.Creation(0, 0);
//		Karen.setBlocks(temp);
//		Karen.calculateTriangle();
//		std::vector<float> block = Karen.getVertex();
//		Micol.setTriangles(block);
//		Micol.Loop();
//	} catch (const std::exception& e) {
//		std::cerr << RED << "Error in " << e.what() << RESET << std::endl;
//	}
//}

//935890145