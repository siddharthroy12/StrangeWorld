#include "World.hpp"
#include <iostream>

World::World() {
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

std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> World::getChunkBlocks(int x, int y) {
	std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> chunkBlocks;

	for (int x2 = 0; x2 < CHUNK_SIZE_X; x2++) {
		for (int y2 = 0; y2 < CHUNK_SIZE_Y; y2++) {
			chunkBlocks[x2][y2] = this->worldMap[(x*CHUNK_SIZE_X)+x2][(y*CHUNK_SIZE_Y)+y2];
		}
	}

	return chunkBlocks;
}

void World::for_each(void (*func)(std::shared_ptr<Chunk> chunk)) {
	for (const auto& kv : loadedChunks) {
		func(kv.second);
	}
}

void World::loadChunk(int x, int y) {
	if (loadedChunks.find(std::to_string(x)+"-"+std::to_string(y)) == loadedChunks.end()) {
		std::cout << "Chunk " << "X: " << x << " " << "Y: " << y << " loaded" << std::endl;
		loadedChunks[std::to_string(x)+"-"+std::to_string(y)] = std::shared_ptr<Chunk>(new Chunk(this->getChunkBlocks(x,y), x, y));
	}
}

void World::unloadChunk(int x, int y) {
	if (loadedChunks.find(std::to_string(x)+"-"+std::to_string(y)) != loadedChunks.end()) {
		std::cout << "Chunk " << "X: " << x << " " << "Y: " << y << " unloaded" << std::endl;
		loadedChunks.erase(std::to_string(x)+"-"+std::to_string(y));
	}
	
}

World::~World() {
	std::cout << "World object deleted" << std::endl;
}