#pragma once

# include "Texture.hpp"
class Texture;
# include "utils/Voxel.hpp"
class Voxel;

class VertexCreator {
private:
	std::vector<std::vector<float>>	faces;
	std::vector<float>				triangles;
	std::vector<Voxel>				&blocks;
	Texture							texture;

public:
	VertexCreator();
	~VertexCreator();

	std::vector<float>	getVertex();
	void				setBlocks(std::vector<Voxel> &input);
	void				directionCheck(Pos input);
	void				calculateTriangle();
	//void				faceCheck();
	//void				fovCheck();

};
