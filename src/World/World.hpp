#ifndef WORLD_HPP
#define WORLD_HPP


#include <unordered_map>
#include <memory>
#include "Chunk.hpp"
#include "raylib.h"

#define WORLD_SIZE_X 3500
#define WORLD_SIZE_Y 1800



class World {
	private:
		std::unordered_map<std::string, std::unique_ptr<Chunk>> loadedChunks;
		Block worldMap[WORLD_SIZE_X][WORLD_SIZE_Y];
	public:
		World();
		void loadChunk(int x, int y);
		void unloadChunk(int x, int y);
		~World();
	
};

#endif