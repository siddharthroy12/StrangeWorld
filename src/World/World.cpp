#include <iostream>
#include <unordered_map>
#include <memory>
#include <thread>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "../../libs/sr_resolve/sr_resolve.h"
#include "Chunk.hpp"
#include "../Sizes/WorldSize.hpp"
#include "../Sizes/TileSize.hpp"


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

	void setBlock(int x, int y, Block block) {
		std::cout << x << "," << y << std::endl;
		map[x][y] = block;
		std::cout << "BlockX: "<< x << "," << "BlockY:" << y << std::endl;

		int chunkX = std::ceil(x / CHUNK_SIZE_X);
		int chunkY = std::ceil(y / CHUNK_SIZE_Y);
		std::cout << "ChunkX: "<< chunkX << "," << "ChunkY:" << chunkY << std::endl;

		if (loadedChunks.count(std::to_string(chunkX)+"-"+std::to_string(chunkY))) {
			loadedChunks[std::to_string(chunkX)+"-"+std::to_string(chunkY)]->updateChunk(x - chunkX*CHUNK_SIZE_X, y - chunkY*CHUNK_SIZE_Y, block);
		}

	}

	std::vector<sr_sort_pair> sortIndexes(std::vector<sr_sort_pair> times) {
		sr_sort_pair key;
		int i, j;
		int length = times.size();

		for (i = 1; i < length; i++) {
			key = times[i];
			j = i - 1;

			while(j >= 0 && times[j].time > key.time) {
				times[j+1] = times[j];
				j = j -1;
			}

			times[j + 1] = key;

		}

		return times;
	}

	sr_rec rectangeToSrRec(Rectangle rect) {
		return (sr_rec){
			rect.x,
			rect.y,
			rect.width,
			rect.height
		};
	}

	void moveAndCollide(Vector2 *position, Vector2 *velocity, Vector2 hitbox) {
		// Position of block entity is in
		int blockX = std::ceil(position->x / (BLOCK_TILE_SIZE))-1;
		int blockY = std::ceil(position->y / (BLOCK_TILE_SIZE))-1;

		int range = std::ceil(Vector2Length(Vector2Subtract(*position, (Vector2){ position->x - (hitbox.x/2), position->y - (hitbox.y/2) })) / BLOCK_TILE_SIZE);

		std::vector<Rectangle> rectsToCheck;

		// This can be optimized I think
		for (int x = blockX - range; x <= blockX + range; x++) {
			for (int y = blockY - range; y <= blockY + range; y++) {
				if (x > -1 && x < WORLD_SIZE_X && y > -1 && y < WORLD_SIZE_Y) {
					if (map[x][y] != Block::AIR) {
						rectsToCheck.push_back((Rectangle){
							.x = (float)x * BLOCK_TILE_SIZE,
							.y = (float)y * BLOCK_TILE_SIZE,
							.width = (float)BLOCK_TILE_SIZE,
							.height = (float)BLOCK_TILE_SIZE
						});
					}
				}
			}
		}

		std::vector<sr_sort_pair> times;
		sr_vec2 cp, cn;
		float time = 0;

		sr_rec hitbox_rec = {
			position->x - (hitbox.x/2),
			position->y - (hitbox.y/2),
			hitbox.x,
			hitbox.y
		};

		for (int i = 0; i < rectsToCheck.size(); i++) {
			sr_dynamic_rect_vs_rect(hitbox_rec, rectangeToSrRec(rectsToCheck[i]), (sr_vec2){velocity->x, velocity->y}, &cp, &cn, &time, GetFrameTime());
			// times[i].index = i;
			// times[i].time = time;
			times.push_back((sr_sort_pair){ .index = i, .time = time });
		}

		times = sortIndexes(times);

		for (int i = 0; i < rectsToCheck.size(); i++) {  
			if (sr_dynamic_rect_vs_rect(hitbox_rec, rectangeToSrRec(rectsToCheck[times[i].index]),  (sr_vec2){velocity->x, velocity->y}, &cp, &cn, &time, GetFrameTime())) {
				position->x = cp.x;
				position->y = cp.y;

				if (fabs(cn.x)) {
					velocity->x = 0;
				}

				if (fabs(cn.y)) {
					velocity->y = 0;
				}
			}
		}

		position->x += velocity->x * GetFrameTime();
		position->y += velocity->y * GetFrameTime();
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