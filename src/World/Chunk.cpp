#include "Chunk.hpp"
#include "../System/ResourceManager.hpp"
#include "../Resources/GameplayResource.hpp"


Chunk::Chunk(Block **blocks) {
	this->chunkTexture = LoadRenderTexture(BLOCK_TILE_SIZE * CHUNK_SIZE_X, BLOCK_TILE_SIZE * CHUNK_SIZE_Y);

	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int y = 0; y < CHUNK_SIZE_Y; y++) {
			this->blocks[x][y] = blocks[x][y];
		}
	}

	std::shared_ptr<GameplayResource> gameplayResource = std::dynamic_pointer_cast<GameplayResource>(ResourceManager::getResource("GameResources"));

	BeginTextureMode(this->chunkTexture);
	
	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int y = 0; y < CHUNK_SIZE_Y; y++) {
			if (this->blocks[x][y] == Block::DIRT) {
				DrawTexturePro(
					gameplayResource->tileAtlas,
					(Rectangle){ 0, 0, 16, 16 },
					(Rectangle){BLOCK_TILE_SIZE * x, BLOCK_TILE_SIZE * y, (BLOCK_TILE_SIZE * x) + BLOCK_TILE_SIZE, (BLOCK_TILE_SIZE * y) + BLOCK_TILE_SIZE },
					(Vector2){ 0.0f, 0.0f },
					0,
					WHITE
				);
			}
		}
	}


	EndTextureMode();
}

void Chunk::generateChunk() { }
void Chunk::renderChunk() {

}
void updateChunk(int x, int y, Block block) {} 
Chunk::~Chunk() {}