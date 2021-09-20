#ifndef WORLD_HPP
#define WORLD_HPP

#include <unordered_map>
#include "../Blocks/Blocks.hpp"
#include "raylib.h"

#define WORLD_SIZE_X 3500
#define WORLD_SIZE_Y 1800

#define CHUNK_SIZE_X 100
#define CHUNK_SIZE_Y 100

class Chunk {
	private:
		Block blocks[CHUNK_SIZE_X][CHUNK_SIZE_X];
		RenderTexture2D chunkTexture;

	public:
		Chunk();
		void generateChunk();
		void renderChunk();
		void updateChunk(int x, int y, Block);
		~Chunk();
};

class World {
	private:
		std::unordered_map<std::pair<int, int>, Chunk*> loadedChunks;
	public:
		void loadChunk(int x, int y);
		void unloadChunk(int x, int y);
		~World();
	
};

#endif