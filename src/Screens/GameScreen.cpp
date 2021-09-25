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
#include "../Entities/Player.hpp"

GameScreen::GameScreen() {
	// Load necessary resources
	ResourceManager::loadResource(std::shared_ptr<Resource>(static_cast<Resource*>(new GameplayResource())));

	// Start background thread
	this->backgroundThread = std::thread([this]() { this->backgroundThreadCallback(); });

	// Camera
	this->camera = (Camera2D){
		.offset = (Vector2){ 1366/2, 768/2 }, // Remind me to fix this
		.target = (Vector2){ 0.0f, 0.0f },
		.rotation = 0.0f,
		.zoom = 5.0f
	};

	// Create player entity
	EntitySystem::create(std::shared_ptr<Entity>(static_cast<Entity*>(new Player())));
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
					world.loadChunk(x, y);
				}
			}
		}

		// Store the positons of chunk to unload
		std::vector<int> chunksToUnloadX;
		std::vector<int> chunksToUnloadY;

		// Get the postion of chunk to unload
		for (const auto& i : world.loadedChunks) {
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
			world.unloadChunk(chunksToUnloadX[i], chunksToUnloadY[i]);
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
	for (const auto& i : world.loadedChunks) {
		i.second->loadTexture();
	}
}

void GameScreen::render() {
	
	int chunkX = std::ceil(this->camera.target.x / (BLOCK_TILE_SIZE*CHUNK_SIZE_X))-1;
	int chunkY = std::ceil(this->camera.target.y / (BLOCK_TILE_SIZE*CHUNK_SIZE_Y))-1;
	
	// Draw outside camera
	DrawText(TextFormat("ChunkX: %d", chunkX), 0,0, 20 , BLACK);
	DrawText(TextFormat("ChunkY: %d", chunkY), 0,25, 20 , BLACK);

	// Draw inside camera
	BeginMode2D(camera);
		// Render chunks
		for (const auto& i : world.loadedChunks) {
			i.second->renderChunk();
		}

		// Render entities
		for (const auto& i : EntitySystem::_entities) {
			i.second->render();
		}

		// Draw World border
		DrawRectangleLines(0, 0,WORLD_SIZE_X*BLOCK_TILE_SIZE,WORLD_SIZE_Y*BLOCK_TILE_SIZE, RED);
	
	EndMode2D();
}

GameScreen::~GameScreen() {
	this->endBackgroundThread = true;
	this->backgroundThread.join();
}