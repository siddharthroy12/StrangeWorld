#include "Chunk.hpp"
#include "../System/ResourceManager.hpp"
#include <iostream>
#include "../Resources/GameplayResource.hpp"


Chunk::Chunk(std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> _blocks, int x, int y) {
	this->posX = x; this->posY = y;

	camera.position = (Vector3){ 0.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

	this->tempMesh = GenMeshCube(1, 1, 1);
	//this->chunkTexture = LoadRenderTexture(BLOCK_TILE_SIZE * CHUNK_SIZE_X, BLOCK_TILE_SIZE * CHUNK_SIZE_Y);

	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int y = 0; y < CHUNK_SIZE_Y; y++) {
			this->blocks[x][y] = _blocks[x][y];
		}
	}

	std::shared_ptr<GameplayResource> gameplayResource = std::dynamic_pointer_cast<GameplayResource>(ResourceManager::getResource("GameplayResource"));

	// BeginTextureMode(this->chunkTexture);
	
	// for (int x = 0; x < CHUNK_SIZE_X; x++) {
	// 	for (int y = 0; y < CHUNK_SIZE_Y; y++) {
	// 		if (this->blocks[x][y] == Block::DIRT) {
	// 			ImageDrawRectangle(
	// 				&this->chunkImage,
	// 				(float)BLOCK_TILE_SIZE * x,
	// 				(float)BLOCK_TILE_SIZE * y,
	// 				(float)(BLOCK_TILE_SIZE * x) + BLOCK_TILE_SIZE,
	// 				(float)(BLOCK_TILE_SIZE * y) + BLOCK_TILE_SIZE,
	// 				GREEN
	// 			);
	// 			// ImageDraw(
	// 			// 	&this->chunkImage,
	// 			// 	gameplayResource->tileAtlas,
	// 			// 	(Rectangle){ 0, 0, 16, 16 },
	// 			// 	(Rectangle){(float)BLOCK_TILE_SIZE * x, (float)BLOCK_TILE_SIZE * y, (float)(BLOCK_TILE_SIZE * x) + BLOCK_TILE_SIZE, (float)(BLOCK_TILE_SIZE * y) + BLOCK_TILE_SIZE },
	// 			// 	(Color){ 0, 0, 0, 0 }
	// 			// );
	// 			// DrawTexturePro(
	// 			// 	gameplayResource->tileAtlas,
	// 			// 	(Rectangle){ 0, 0, 16, 16 },
	// 			// 	(Rectangle){(float)BLOCK_TILE_SIZE * x, (float)BLOCK_TILE_SIZE * y, (float)(BLOCK_TILE_SIZE * x) + BLOCK_TILE_SIZE, (float)(BLOCK_TILE_SIZE * y) + BLOCK_TILE_SIZE },
	// 			// 	(Vector2){ 0.0f, 0.0f },
	// 			// 	0,
	// 			// 	WHITE
	// 			// );
	// 		}
	// 	}
	// }

	// EndTextureMode();
	this->needToLoadTexture = true;
}

int Chunk::getPosX() const {
	return this->posX;
}

int Chunk::getPosY() const {
	return this->posY;
}

void Chunk::renderChunk() {
	std::shared_ptr<GameplayResource> gameplayResource = std::dynamic_pointer_cast<GameplayResource>(ResourceManager::getResource("GameplayResource"));
	DrawTexture(this->chunkTexture.texture, this->posX*CHUNK_SIZE_X*BLOCK_TILE_SIZE, this->posY*CHUNK_SIZE_Y*BLOCK_TILE_SIZE, WHITE);
}

void Chunk::loadTexture() {
	if (this->needToLoadTexture) {
		this->chunkTexture = LoadRenderTexture(BLOCK_TILE_SIZE * CHUNK_SIZE_X, BLOCK_TILE_SIZE * CHUNK_SIZE_Y);
		std::cout << "yes" << std::endl;
		BeginTextureMode(this->chunkTexture);
		ClearBackground(RAYWHITE);
			BeginMode3D(camera);
				DrawCube((Vector3){ 0.0f, 0.0f, 0.0f }, 1, 1, 1, RED);
				DrawGrid(10, 1.0f);
			EndMode3D();
			DrawRectangle(0,0, 100, 100, RED);
		EndTextureMode();
		this->needToLoadTexture = false;
	}
}

void Chunk::updateChunk(int x, int y, Block block) {
	this->needToLoadTexture = true;
}

Chunk::~Chunk() {
	std::cout << "Thi is called" << std::endl;
	UnloadRenderTexture(this->chunkTexture);
	UnloadImage(this->chunkImage);
}