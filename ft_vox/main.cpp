#include "headers/inclusion.h"
#include "WorldGenerator.hpp"
#include "headers/colors.h"

int main (int ac, char **av) {
	(void)av;
	if (ac != 3)
		return -1;
	try {
		WorldGenerator world(av[1], av[2]);
		world.Creation(0, 0);
	} catch (const std::exception& e) {
		std::cerr << RED << "Error in " << e.what() << RESET << std::endl;
	}
}

//935890145