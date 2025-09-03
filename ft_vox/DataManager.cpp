#include "DataManager.hpp"

DataManager::DataManager() {}
DataManager::~DataManager() {}

void	DataManager::saveSeed(std::string seed, std::string worldName) {
	if (!this->checkSeed(seed))
		throw DataManager::InvalidSeed();
	std::string baseDir = "./worlds";
	std::string worldDir = baseDir + "/" + worldName;
	std::string filePath = worldDir + "/seed.txt";

	if (mkdir(baseDir.c_str(), 0755) == -1 && errno != EEXIST)
		throw DataManager::FolderCreation();
	if (mkdir(worldDir.c_str(), 0755) == -1 && errno != EEXIST)
		throw DataManager::FolderCreation();
	std::ofstream outFile(filePath.c_str());
	if (!outFile.is_open())
		throw DataManager::SeedSaving();

	outFile << seed;
	outFile.close();
}

std::string	DataManager::getSeed(std::string worldName) {
	std::string filePath = "./worlds/" + worldName + "/seed.txt";
	std::ifstream inFile(filePath.c_str());
	if (!inFile.is_open())
		throw DataManager::SeedReading();

	std::stringstream buffer;
	buffer << inFile.rdbuf();
	inFile.close();
	return buffer.str();
}

//Verifica la validità del seed
bool	DataManager::checkSeed(std::string str) {
	if (str.empty())
		return false;
	if (str.length() > 19)
		return false;
	for (char c : str)
		if (!std::isdigit(c))
			return false;
	return true;
}

void	DataManager::saveChunk(std::vector<Voxel>& blocks, int x, int z, std::string& worldName) {
	std::string worldDir = "./worlds/" + worldName;
	std::string chunkFile = worldDir + "/chunk_" + std::to_string(x) + "_" + std::to_string(z) + ".txt";

	std::ofstream outFile(chunkFile.c_str());
	if (!outFile.is_open())
		throw DataManager::ChunkSaving();

	for (size_t i = 0; i < blocks.size(); ++i) {
		outFile << std::to_string(blocks[i].block);
		if (i < blocks.size() - 1)
			outFile << "\n";
	}
	outFile.close();
}

std::vector<int>	DataManager::getChunk(int x, int z, std::string& worldName) {
	std::string chunkFile = "./worlds/" + worldName + "/chunk_" + std::to_string(x) + "_" + std::to_string(z) + ".txt";

	std::ifstream inFile(chunkFile.c_str());
	if (!inFile.is_open())
		throw DataManager::ChunkReading();

	std::vector<int> blocks;
	int block;
	while (inFile >> block)
		blocks.push_back(block);

	inFile.close();
	return blocks;
}

//Ricerca se il chunck è stato salvato in precedenza
bool	DataManager::searchChunk(int x, int z, std::string& worldName) {
	std::string chunkFile = "./worlds/" + worldName + "/chunk_" + std::to_string(x) + "_" + std::to_string(z) + ".txt";

	std::ifstream inFile(chunkFile.c_str());
	if (!inFile.is_open())
		return false;
	return true;
}