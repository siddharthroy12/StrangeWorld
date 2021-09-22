#ifndef CHUNK_HPP
#define CHUNK_HPP

#define CHUNK_SIZE_X 100
#define CHUNK_SIZE_Y 100

#include <array>

#include "../Blocks/Blocks.hpp"
#include "raylib.h"

class Chunk {
	private:
		std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> blocks;
		RenderTexture2D chunkTexture;
		int posX;
		int posY;

	public:
		Chunk(std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> blocks, int x, int y);
		void renderChunk();
		void updateChunk(int x, int y, Block block);
		~Chunk();
};

#endif