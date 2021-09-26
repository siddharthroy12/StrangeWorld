#include "Chunk.hpp"
#include "../System/ResourceManager.hpp"
#include <iostream>
#include "../Resources/GameplayResource.hpp"
#include "../../libs/raytile/raytile.h"

Chunk::Chunk(std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> _blocks, int x, int y) {
	this->posX = x; this->posY = y; // Set the position of chunk

	camera.position = (Vector3){ ((float)CHUNK_SIZE_X/2), 20.0f, -((float)CHUNK_SIZE_Y/2)}; // Camera position
    camera.target = (Vector3){ ((float)CHUNK_SIZE_X/2), 0.0f, -((float)CHUNK_SIZE_Y/2) }; // Camera looking at point
    camera.up = (Vector3){ 0.0f, 0.0f, 1.0f }; // Camera up vector (rotation towards target)
    camera.fovy = (float)CHUNK_SIZE_Y; // Camera field-of-view Y
	camera.projection = CAMERA_ORTHOGRAPHIC; // To draw without perspective
	
	// Load blocks data and generate tilemap coords
	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int y = 0; y < CHUNK_SIZE_Y; y++) {
			this->blocks[x][y] = _blocks[x][y];

			if (_blocks[x][y] == Block::DIRT) {
				this->tileTextureMap[x][y][0] = 0;
				this->tileTextureMap[x][y][1] = 0;
			} else {
				this->tileTextureMap[x][y][0] = 0;
				this->tileTextureMap[x][y][1] = 3;
			}
			
		}
	}

	
	
	this->needToRenderTexture = true;
	this->needToLoadModel = true;
	this->needToLoadTexture = true;
	this->needToUnloadModal = false;
}

int Chunk::getPosX() const {
	return this->posX;
}

int Chunk::getPosY() const {
	return this->posY;
}

void Chunk::renderChunk() {
	std::shared_ptr<GameplayResource> gameplayResource = std::dynamic_pointer_cast<GameplayResource>(ResourceManager::getResource("GameplayResource"));
	
	DrawTextureEx(
		this->chunkTexture.texture,
		(Vector2){
			.x = (this->posX*CHUNK_SIZE_X*BLOCK_TILE_SIZE) + CHUNK_SIZE_X*BLOCK_TILE_SIZE,
			.y = (this->posY*CHUNK_SIZE_Y*BLOCK_TILE_SIZE) + CHUNK_SIZE_Y*BLOCK_TILE_SIZE
		},
		180.0f,
		1,
		WHITE
	);
}

void Chunk::loadTexture() {

	// Load model and mesh for tilemap
	if (this->needToLoadModel) {
		if (this->needToUnloadModal) {
			UnloadModel(this->model);
		}

		// Generate tilemap mesh
		this->mesh = rtl_gen_tile_mesh(1, CHUNK_SIZE_X, CHUNK_SIZE_Y, 8, 8, this->tileTextureMap);

		std::shared_ptr<GameplayResource> gameplayResource = std::dynamic_pointer_cast<GameplayResource>(ResourceManager::getResource("GameplayResource"));
		UploadMesh(&this->mesh, false);
		this->model = LoadModelFromMesh(this->mesh);
		model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = gameplayResource->tileAtlas;
		this->needToLoadModel = false;
	}

	// Load Texure only once
	if (this->needToLoadTexture) {
		this->chunkTexture = LoadRenderTexture(BLOCK_TILE_SIZE * CHUNK_SIZE_X, BLOCK_TILE_SIZE * CHUNK_SIZE_Y);
		this->needToLoadTexture = false;
	}

	// Render tilemap when needed
	if (this->needToRenderTexture) {
		
		BeginTextureMode(this->chunkTexture);
		ClearBackground((Color){ 0,0,0,0 });
			BeginMode3D(camera);
				DrawModel(this->model, (Vector3){ 0, 0.0f, 0 }, 1, WHITE);
				DrawModelWires(this->model, (Vector3){ 0, 0.0f, 0 }, 1, BLACK);
			EndMode3D();
		EndTextureMode();
		
		this->needToRenderTexture = false;
	}
}


// Incomplete function
void Chunk::updateChunk(int x, int y, Block block) {
	this->blocks[x][y] = block;

	if (block == Block::AIR) {
		this->tileTextureMap[x][y][0] = 0;
		this->tileTextureMap[x][y][1] = 3;
	}


	this->needToLoadModel = true;
	this->needToRenderTexture = true;
	this->needToUnloadModal = true;
}

Chunk::~Chunk() {
	UnloadRenderTexture(this->chunkTexture);
	UnloadModel(this->model);
}