#include "GameScreen.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include "../Utils/Assets.hpp"
#include "../System/ScreenManager.hpp"
#include "../System/ResourceManager.hpp"
#include "../Resources/GameplayResource.hpp"
#include "../System/EntitySystem.hpp"
#include "../System/Game.hpp"
#include "../Entities/Player.hpp"
#include "../Sizes/WorldSize.hpp"
#include "../Sizes/RenderSize.hpp"
#include "raymath.h"

GameScreen::GameScreen() {
	// Load necessary resources
	ResourceManager::loadResource(std::shared_ptr<Resource>(static_cast<Resource*>(new GameplayResource())));

	// Start background thread
	this->backgroundThread = std::thread([this]() { this->backgroundThreadCallback(); });

	// Camera
	this->camera = (Camera2D){
		.offset = (Vector2){ RENDER_WIDTH/2, RENDER_HEIGHT/2 }, // Remind me to fix this
		.target = (Vector2){ 0.0f, 0.0f },
		.rotation = 0.0f,
		.zoom = 2.0f
	};

	// Create player entity
	EntitySystem::create(std::shared_ptr<Entity>(static_cast<Entity*>(new Player())));

	World::generateMap();
}

void GameScreen::backgroundThreadCallback() {
	// Range of chunk to be loaded at a time
	int chunkLoadRange = 1;

	while (!this->endBackgroundThread) {

		// Positon of chunk we are looking at
		int chunkX = std::ceil(this->camera.target.x / (BLOCK_TILE_SIZE*CHUNK_SIZE_X))-1;
		int chunkY = std::ceil(this->camera.target.y / (BLOCK_TILE_SIZE*CHUNK_SIZE_Y))-1;
		
		// Load chunk in range
		for (int x = chunkX - chunkLoadRange; x <= chunkX + chunkLoadRange; x++) {
			for (int y = chunkY - chunkLoadRange; y <= chunkY + chunkLoadRange; y++) {
				if ((x > -1) && (x < WORLD_SIZE_X/CHUNK_SIZE_X) && (y > -1) && (y < WORLD_SIZE_Y/CHUNK_SIZE_Y)) {
					World::loadChunk(x, y);
				}
			}
		}

		// Store the positons of chunk to unload
		std::vector<int> chunksToUnloadX;
		std::vector<int> chunksToUnloadY;

		// Get the postion of chunk to unload
		for (const auto& i : World::loadedChunks) {
			if (
				((std::abs(i.second->getPosX() - chunkX) > chunkLoadRange)) ||
				((std::abs(i.second->getPosY() - chunkY) > chunkLoadRange))
			) {
				chunksToUnloadX.push_back(i.second->getPosX());
				chunksToUnloadY.push_back(i.second->getPosY());
			}
		}

		// Unload chunks
		for (int i = 0; i < chunksToUnloadX.size(); i++) {
			World::unloadChunk(chunksToUnloadX[i], chunksToUnloadY[i]);
		}
	}
}

void GameScreen::update() {
	// Update entites
	for (const auto& i : EntitySystem::_entities) {
		i.second->update();

		// Camera follows player
		if (i.second->getType() == "Player") {
			camera.target = std::dynamic_pointer_cast<Player>(i.second)->getPositon();
		}
	}

	// Load texures (frambuffer) of loaded chunks
	for (const auto& i : World::loadedChunks) {
		i.second->loadTexture();
	}

	// Position of block the cursor pointing to
	
	int blockX = std::ceil(GetScreenToWorld2D(Game::virtualMousePos, camera).x / (BLOCK_TILE_SIZE))-1;
	int blockY = std::ceil(GetScreenToWorld2D(Game::virtualMousePos, camera).y / (BLOCK_TILE_SIZE))-1;

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		//std::cout << blockX << std::endl;
		World::setBlock(blockX, blockY, Block::AIR);
	}
}

void GameScreen::render() {
	// Position of block entity is in
	int blockX = std::ceil(camera.target.x / (BLOCK_TILE_SIZE))-1;
	int blockY = std::ceil(camera.target.y / (BLOCK_TILE_SIZE))-1;
	
	// Find Range of blocks to check
	int range = std::ceil(Vector2Length(Vector2Subtract(camera.target, (Vector2){ camera.target.x - (16/2), camera.target.y - (32/2) })) / BLOCK_TILE_SIZE);

	int chunkX = std::ceil(this->camera.target.x / (BLOCK_TILE_SIZE*CHUNK_SIZE_X))-1;
	int chunkY = std::ceil(this->camera.target.y / (BLOCK_TILE_SIZE*CHUNK_SIZE_Y))-1;
	
	// Draw outside camera
	DrawText(TextFormat("ChunkX: %d", chunkX), 0,0, 20 , BLACK);
	DrawText(TextFormat("ChunkY: %d", chunkY), 0,25, 20 , BLACK);

	// Draw inside camera
	BeginMode2D(camera);
		// Render chunks
		for (const auto& i : World::loadedChunks) {
			i.second->renderChunk();
		}

		// Render chunk border
		DrawRectangleLinesEx((Rectangle) {
			.x = (float)chunkX * CHUNK_SIZE_X * BLOCK_TILE_SIZE,
			.y = (float)chunkY * CHUNK_SIZE_Y * BLOCK_TILE_SIZE,
			.width = (float)CHUNK_SIZE_X * BLOCK_TILE_SIZE,
			.height = (float)CHUNK_SIZE_Y * BLOCK_TILE_SIZE
		}, 1, RED);

		// This can be optimized I think
		for (int x = blockX - range; x <= blockX + range; x++) {
			for (int y = blockY - range; y <= blockY + range; y++) {
				if (x > -1 && x < WORLD_SIZE_X && y > -1 && y < WORLD_SIZE_Y) {
					DrawRectangleLinesEx((Rectangle) {
							.x = (float)x * BLOCK_TILE_SIZE,
							.y = (float)y * BLOCK_TILE_SIZE,
							.width = (float)BLOCK_TILE_SIZE,
							.height = (float)BLOCK_TILE_SIZE
					}, 1, GREEN);
				}
			}
		}

		// Render entities
		for (const auto& i : EntitySystem::_entities) {
			i.second->render();
		}

		// Draw World border
		DrawRectangleLines(0, 0, WORLD_SIZE_X*BLOCK_TILE_SIZE,WORLD_SIZE_Y*BLOCK_TILE_SIZE, RED);
	
	EndMode2D();
}

GameScreen::~GameScreen() {
	this->endBackgroundThread = true;
	this->backgroundThread.join();
}