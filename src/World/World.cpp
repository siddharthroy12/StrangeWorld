#include <iostream>
#include <unordered_map>
#include <memory>
#include <thread>
#include "raylib.h"
#include "Chunk.hpp"
#include "WorldSize.hpp"


namespace World {
	typedef std::unordered_map<std::string, std::shared_ptr<Chunk>> ChunkMap;

	std::array<std::array<Block, WORLD_SIZE_Y>, WORLD_SIZE_X> map; // Contains data of all block in the world
	ChunkMap loadedChunks;

	void generateMap() {
		// For now fill the half of the world with dirt
		for (int x = 0; x < WORLD_SIZE_X; x++) {
			for (int y = 0; y < WORLD_SIZE_Y; y++) {
				if (y > WORLD_SIZE_Y/2) {
					map[x][y] = Block::DIRT;
				} else {
					map[x][y] = Block::AIR;
				}
			}
		}
	}

	std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> getChunkBlocks(int x, int y) {
		std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> chunkBlocks;

		for (int x2 = 0; x2 < CHUNK_SIZE_X; x2++) {
			for (int y2 = 0; y2 < CHUNK_SIZE_Y; y2++) {
				chunkBlocks[x2][y2] = map[(x*CHUNK_SIZE_X)+x2][(y*CHUNK_SIZE_Y)+y2];
			}
		}

		return chunkBlocks;
	}

	void loadChunk(int x, int y) {
		if (loadedChunks.find(std::to_string(x)+"-"+std::to_string(y)) == loadedChunks.end()) {
			loadedChunks[std::to_string(x)+"-"+std::to_string(y)] = std::shared_ptr<Chunk>(new Chunk(getChunkBlocks(x,y), x, y));
		}
	}

	void unloadChunk(int x, int y) {
		if (loadedChunks.find(std::to_string(x)+"-"+std::to_string(y)) != loadedChunks.end()) {
			loadedChunks.erase(std::to_string(x)+"-"+std::to_string(y));
		}
	}

	void unloadWorld() {
		loadedChunks.clear();
	}
}