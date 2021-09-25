#ifndef WORLD_HPP
#define WORLD_HPP

#include <unordered_map>
#include <memory>
#include <thread>
#include "raylib.h"
#include "Chunk.hpp"

#define WORLD_SIZE_X 3500
#define WORLD_SIZE_Y 1800

typedef std::unordered_map<std::string, std::shared_ptr<Chunk>> ChunkMap;

class World {
	private:
		std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> getChunkBlocks(int x, int y);
		std::array<std::array<Block, WORLD_SIZE_Y>, WORLD_SIZE_X> worldMap; // Contains data of all block in the world
	public:
		World();
		ChunkMap loadedChunks;
		void loadChunk(int x, int y);
		void unloadChunk(int x, int y);
		~World();
	
};

#endif