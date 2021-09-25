#include "Chunk.hpp"
#include "../System/ResourceManager.hpp"
#include <iostream>
#include "../Resources/GameplayResource.hpp"
#include "../../libs/raytile/raytile.h"

Chunk::Chunk(std::array<std::array<Block, CHUNK_SIZE_Y>, CHUNK_SIZE_X> _blocks, int x, int y) {
	this->posX = x; this->posY = y; // Set the position of chunk

	camera.position = (Vector3){ 0.0f, 20.0f, 0.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; // Camera looking at point
    camera.up = (Vector3){ 0.0f, 0.0f, 1.0f }; // Camera up vector (rotation towards target)
    camera.fovy = 45.0f; // Camera field-of-view Y
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
				this->tileTextureMap[x][y][1] = 0;
			}
			
		}
	}

	// Generate tilemap mesh
	this->mesh = rtl_gen_tile_mesh(1, CHUNK_SIZE_X, CHUNK_SIZE_Y, 8, 8, this->tileTextureMap);
	
	this->needToRenderTexture = true;
	this->needToLoadModel = true;
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

	// Load model and mesh for tilemap
	if (this->needToLoadModel) {
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
				DrawModel(this->model, (Vector3){ -22.5f, 0.0f, 22.5f }, 0.5, WHITE);
				DrawModelWires(this->model, (Vector3){ -22.5f, 0.0f, 22.5f }, 0.5, BLACK);
			EndMode3D();
		EndTextureMode();
		
		this->needToRenderTexture = false;
	}
}


// Incomplete function
void Chunk::updateChunk(int x, int y, Block block) {
	this->needToLoadModel = true;
	this->needToRenderTexture = true;
}

Chunk::~Chunk() {
	UnloadRenderTexture(this->chunkTexture);
	UnloadModel(this->model);
}