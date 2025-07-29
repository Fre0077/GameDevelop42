#pragma once

# include "Texture.hpp"
class Texture;
# include "utils/Voxel.hpp"
class Voxel;

class VertexCreator {
private:
	std::vector<Voxel>	blocks;
	std::vector<float>	triangles;
	Texture				texture;

public:
	VertexCreator();
	~VertexCreator();

	std::vector<float>	getVertex();
	void				directionCheck(float x, float y, float z);
	void				setBlocks(std::vector<Voxel> input);
	void				calculateTriangle();
	void				airCheck();
	//void				faceCheck();
	//void				fovCheck();

};
