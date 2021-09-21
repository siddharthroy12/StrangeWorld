#ifndef CHUNK_HPP
#define CHUNK_HPP

#define CHUNK_SIZE_X 100
#define CHUNK_SIZE_Y 100

#include "../Blocks/Blocks.hpp"
#include "raylib.h"

class Chunk {
	private:
		Block blocks[CHUNK_SIZE_X][CHUNK_SIZE_X];
		RenderTexture2D chunkTexture;

	public:
		Chunk(Block **blocks);
		void generateChunk();
		void renderChunk();
		void updateChunk(int x, int y, Block block);
		~Chunk();
};

#endif