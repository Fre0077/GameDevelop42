#include "headers/inclusion.h"
#include "WorldGenerator.hpp"
#include "VertexCreator.hpp"
#include "headers/colors.h"
#include "Rendering.hpp"

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
		
		std::vector<float> oneBlock;
		for (size_t i = 0; i < 180 && i < block.size(); ++i)
			oneBlock.push_back(block[i]);

		Micol.setTriangles(oneBlock);
		Micol.Loop();
	} catch (const std::exception& e) {
		std::cerr << RED << "Error in " << e.what() << RESET << std::endl;
	}
}

//935890145