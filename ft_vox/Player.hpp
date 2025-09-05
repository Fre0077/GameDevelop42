#pragma once

# include "headers/inclusion.h"

# include "WorldGenerator.hpp"
class WorldGenerator;
# include "utils/Voxel.hpp"
class Voxel;

class Player {
private:
	std::string	name;
	posChunck	chunck;
	Pos			coordinate;

public:
	Player(std::string inputName);
	~Player();

	void	newChunck(WorldGenerator &Notch, std::vector<float> &triangol);
	void	printPlayerInfo();
	int		changePosition(Pos &newPos);

	class ErrorWindow : public std::exception {
	public:
		const char* what() const noexcept override {
			return "Player: couldn't create the reqeust window";
		}
	};
};