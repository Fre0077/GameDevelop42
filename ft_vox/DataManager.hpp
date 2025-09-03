#pragma once

# include "headers/inclusion.h"

# include "utils/Voxel.hpp"
class Voxel;

class DataManager {
public:
	DataManager();
	~DataManager();

	std::string	getSeed(std::string worldName);
	void		saveSeed(std::string seed, std::string worldName);
	bool		checkSeed(std::string str);

	std::vector<int>	getChunk(int x, int z, std::string& worldName);
	void				saveChunk(std::vector<Voxel>& blocks, int x, int z, std::string& worldName);
	bool				searchChunk(int x, int z, std::string& worldName);

	class FolderCreation : public std::exception {
	public:
		const char* what() const noexcept override {
			return "DataManager: error during the creation of a folder";
		}
	};

	class SeedSaving : public std::exception {
	public:
		const char* what() const noexcept override {
			return "DataManager: error during the saving of the seed";
		}
	};

	class SeedReading : public std::exception {
	public:
		const char* what() const noexcept override {
			return "DataManager: error during the reading of the seed";
		}
	};

	class InvalidSeed : public std::exception {
	public:
		const char* what() const noexcept override {
			return "DataManager: The given seed is not suitable for the world generation";
		}
	};

	class ChunkSaving : public std::exception {
	public:
		const char* what() const noexcept override {
			return "DataManager: error during the saving of the chunk";
		}
	};

	class ChunkReading : public std::exception {
	public:
		const char* what() const noexcept override {
			return "DataManager: error during the reading of the chunk";
		}
	};
};
