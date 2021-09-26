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

	Rectangle srMoveAndCollide(std::vector<Rectangle> staticRects, Rectangle rectToMove, Vector2 velocity) {
		Rectangle beforeMove = rectToMove;

		rectToMove.x += velocity.x * GetFrameTime();
		rectToMove.y += velocity.y * GetFrameTime();

		Rectangle result = rectToMove;

		for (int i = 0; i < staticRects.size(); i++) {
			sr_rec _result = sr_resolver_rects_collision(
				(sr_rec) {
					.x = staticRects[i].x,
					.y = staticRects[i].y,
					.width = staticRects[i].width,
					.height = staticRects[i].height
				},
				(sr_rec) {
					.x = result.x,
					.y = result.y,
					.width = result.width,
					.height = result.height
				}
			);

			result.x = _result.x;
			result.y = _result.y;
		}

		if (result.x == beforeMove.x && result.y == beforeMove.y) {
			result.x += velocity.x * GetFrameTime();
        	result.y += velocity.y * GetFrameTime();

			for (int i = staticRects.size() -1; i > -1; i--) {
				sr_rec _result = sr_resolver_rects_collision(
					(sr_rec) {
						.x = staticRects[i].x,
						.y = staticRects[i].y,
						.width = staticRects[i].width,
						.height = staticRects[i].height
					},
					(sr_rec) {
						.x = result.x,
						.y = result.y,
						.width = result.width,
						.height = result.height
					}
				);

				result.x = _result.x;
				result.y = _result.y;
			}
		}

		return result;

	}

	Vector2 moveAndCollide(Vector2 position, Vector2 velocity, Rectangle hitbox) {
		// Position of block entity is in
		int blockX = std::ceil(position.x / (BLOCK_TILE_SIZE))-1;
		int blockY = std::ceil(position.y / (BLOCK_TILE_SIZE))-1;

		std::cout << blockX << std::endl;
		// Find Range of blocks to check
		int range = std::ceil(Vector2Length(Vector2Subtract(position, (Vector2){ hitbox.x, hitbox.y })) / BLOCK_TILE_SIZE) + 2;

		Rectangle finalHitboxPosition = hitbox;
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

		finalHitboxPosition = srMoveAndCollide(rectsToCheck, hitbox, velocity);

		return (Vector2) {
			.x = finalHitboxPosition.x + (hitbox.width /2),
			.y = finalHitboxPosition.y + (hitbox.height /2)
		};
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