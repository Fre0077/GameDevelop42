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