#include "World.hpp"
#include <iostream>

World::World() {
	// For now fill the half of the world with dirt
	for (int x = 0; x < WORLD_SIZE_X; x++) {
		for (int y = 0; y < WORLD_SIZE_Y; y++) {
			if (y > WORLD_SIZE_Y/2) {
				worldMap[x][y] = Block::DIRT;
			} else {
				worldMap[x][y] = Block::AIR;
			}
		}
	}
}

// Get blocks from given chunk
std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> World::getChunkBlocks(int x, int y) {
	std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> chunkBlocks;

	for (int x2 = 0; x2 < CHUNK_SIZE_X; x2++) {
		for (int y2 = 0; y2 < CHUNK_SIZE_Y; y2++) {
			chunkBlocks[x2][y2] = this->worldMap[(x*CHUNK_SIZE_X)+x2][(y*CHUNK_SIZE_Y)+y2];
		}
	}

	return chunkBlocks;
}

void World::loadChunk(int x, int y) {
	if (loadedChunks.find(std::to_string(x)+"-"+std::to_string(y)) == loadedChunks.end()) {
		loadedChunks[std::to_string(x)+"-"+std::to_string(y)] = std::shared_ptr<Chunk>(new Chunk(this->getChunkBlocks(x,y), x, y));
	}
}

void World::unloadChunk(int x, int y) {
	if (loadedChunks.find(std::to_string(x)+"-"+std::to_string(y)) != loadedChunks.end()) {
		loadedChunks.erase(std::to_string(x)+"-"+std::to_string(y));
	}
	
}

World::~World() {
	std::cout << "Object: World = Deleted" << std::endl;
}