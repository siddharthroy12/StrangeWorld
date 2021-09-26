#ifndef WORLD_HPP
#define WORLD_HPP

#include <unordered_map>
#include <memory>
#include <thread>
#include "raylib.h"
#include "Chunk.hpp"
#include "../Sizes/WorldSize.hpp"

namespace World {
	typedef std::unordered_map<std::string, std::shared_ptr<Chunk>> ChunkMap;

	extern std::array<std::array<Block, WORLD_SIZE_Y>, WORLD_SIZE_X> map; // Contains data of all block in the world
	extern ChunkMap loadedChunks;

	void generateMap();
	void loadChunk(int x, int y);
	std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> getChunkBlocks(int x, int y);
	void unloadChunk(int x, int y);
	void unloadWorld();

	Vector2 moveAndCollide(Vector2 position, Vector2 velocity, Rectangle hitbox);
}

#endif