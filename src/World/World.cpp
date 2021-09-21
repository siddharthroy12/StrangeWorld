#include "World.hpp"

World::World() {
	for (int x = 0; x < WORLD_SIZE_X; x++) {
		for (int y = 0; y < WORLD_SIZE_Y; y++) {
			if (x > WORLD_SIZE_Y/2) {
				worldMap[x][y] = Block::DIRT;
			} else {
				worldMap[x][y] = Block::AIR;
			}
		}
	}
}

void World::loadChunk(int x, int y) { }
void World::unloadChunk(int x, int y) { }

World::~World() {}