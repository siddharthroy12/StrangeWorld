#include "Chunk.hpp"
#include "../System/ResourceManager.hpp"
#include <iostream>
#include "../Resources/GameplayResource.hpp"


Chunk::Chunk(std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> _blocks, int x, int y) {
	this->posX = x; this->posY = y;

	this->chunkTexture = LoadRenderTexture(BLOCK_TILE_SIZE * CHUNK_SIZE_X, BLOCK_TILE_SIZE * CHUNK_SIZE_Y);

	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int y = 0; y < CHUNK_SIZE_Y; y++) {
			this->blocks[x][y] = _blocks[x][y];
		}
	}

	std::shared_ptr<GameplayResource> gameplayResource = std::dynamic_pointer_cast<GameplayResource>(ResourceManager::getResource("GameplayResource"));

	BeginTextureMode(this->chunkTexture);
	
	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int y = 0; y < CHUNK_SIZE_Y; y++) {
			if (this->blocks[x][y] == Block::DIRT) {
				DrawTexturePro(
					gameplayResource->tileAtlas,
					(Rectangle){ 0, 0, 16, 16 },
					(Rectangle){(float)BLOCK_TILE_SIZE * x, (float)BLOCK_TILE_SIZE * y, (float)(BLOCK_TILE_SIZE * x) + BLOCK_TILE_SIZE, (float)(BLOCK_TILE_SIZE * y) + BLOCK_TILE_SIZE },
					(Vector2){ 0.0f, 0.0f },
					0,
					WHITE
				);
			}
		}
	}

	EndTextureMode();
}

int Chunk::getPosX() const {
	return this->posX;
}

int Chunk::getPosY() const {
	return this->posY;
}

void Chunk::renderChunk() {
	DrawTexture(this->chunkTexture.texture, this->posX*CHUNK_SIZE_X*BLOCK_TILE_SIZE, this->posY*CHUNK_SIZE_Y*BLOCK_TILE_SIZE, WHITE);
}

void updateChunk(int x, int y, Block block) {

}

Chunk::~Chunk() {
	std::cout << "Thi is called" << std::endl;
	//UnloadRenderTexture(this->chunkTexture);
}