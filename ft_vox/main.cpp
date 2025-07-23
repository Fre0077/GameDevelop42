#include "headers/inclusion.h"
#include "WorldGenerator.hpp"
#include "headers/colors.h"

int main (int ac, char **av) {
	(void)av;
	if (ac != 3)
		return -1;
	try {
		WorldGenerator world(av[2]);
		world.Creation(0, 0);
		world.Creation(16, 0);
		world.Creation(0, 16);
		world.Creation(16, 16);
	} catch (const std::exception& e) {
		std::cerr << RED << "Error in " << e.what() << RESET << std::endl;
	}
}

//935890145