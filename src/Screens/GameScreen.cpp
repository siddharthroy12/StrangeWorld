#include "GameScreen.hpp"
#include "../Utils/Assets.hpp"
#include "../System/ScreenManager.hpp"
#include "../System/ResourceManager.hpp"
#include "../Resources/GameplayResource.hpp"
#include "../System/EntitySystem.hpp"
#include "../Entities/Player.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

GameScreen::GameScreen() {
	ResourceManager::loadResource(std::shared_ptr<Resource>(static_cast<Resource*>(new GameplayResource())));

	this->backgroundThread = std::thread([this]() { this->backgroundThreadCallback(); });

	this->camera = (Camera2D){
		.offset = (Vector2){ 1366/2, 768/2 }, // Remind me to fix this
		.target = (Vector2){ 0.0f, 0.0f },
		.rotation = 0.0f,
		.zoom = 5.0f
	};

	EntitySystem::create(std::shared_ptr<Entity>(static_cast<Entity*>(new Player())));
}

void GameScreen::backgroundThreadCallback() {
	int chunkLoadRange = 1;

	while (!this->endBackgroundThread) {
		int chunkX = std::ceil(pos.x / (BLOCK_TILE_SIZE*CHUNK_SIZE_X))-1;
		int chunkY = std::ceil(pos.y / (BLOCK_TILE_SIZE*CHUNK_SIZE_Y))-1;
		
		for (int x = chunkX - chunkLoadRange; x <= chunkX + chunkLoadRange; x++) {
			for (int y = chunkY - chunkLoadRange; y <= chunkY + chunkLoadRange; y++) {
				if ((x > -1) && (x < WORLD_SIZE_X/CHUNK_SIZE_X) && (y > -1) && (y < WORLD_SIZE_Y/CHUNK_SIZE_Y)) {
					world.loadChunk(x, y);
				}
			}
		}

		std::vector<int> chunksToUnloadX;
		std::vector<int> chunksToUnloadY;

		for (const auto& i : world.loadedChunks) {
			if (
				((std::abs(i.second->getPosX() - chunkX) > chunkLoadRange)) ||
				((std::abs(i.second->getPosY() - chunkY) > chunkLoadRange))
			) {
				chunksToUnloadX.push_back(i.second->getPosX());
				chunksToUnloadY.push_back(i.second->getPosY());
			}
		}

		for (int i = 0; i < chunksToUnloadX.size(); i++) {
			world.unloadChunk(chunksToUnloadX[i], chunksToUnloadY[i]);
		}
	}
}

void GameScreen::update() {
	for (const auto& i : EntitySystem::_entities) {
		i.second->update();

		if (i.second->getType() == "Player") {
			camera.target = std::dynamic_pointer_cast<Player>(i.second)->getPositon();
		}
	}

	for (const auto& i : world.loadedChunks) {
		i.second->loadTexture();
	}
}

void GameScreen::render() {
	std::shared_ptr<GameplayResource> gameplayResource = std::dynamic_pointer_cast<GameplayResource>(ResourceManager::getResource("GameplayResource"));
	
	int chunkX = std::ceil(pos.x / (BLOCK_TILE_SIZE*CHUNK_SIZE_X))-1;
	int chunkY = std::ceil(pos.y / (BLOCK_TILE_SIZE*CHUNK_SIZE_Y))-1;
	DrawText(TextFormat("ChunkX: %d", chunkX), 0,0, 20 , BLACK);
	DrawText(TextFormat("ChunkY: %d", chunkY), 0,25, 20 , BLACK);

	BeginMode2D(camera);
	
		world.for_each([](std::shared_ptr<Chunk> chunk) {
			chunk->renderChunk();
		});

		for (const auto& i : EntitySystem::_entities) {
			i.second->render();
		}

		DrawRectangleLines(0, 0, CHUNK_SIZE_X*BLOCK_TILE_SIZE, CHUNK_SIZE_Y*BLOCK_TILE_SIZE, RED);
	
	EndMode2D();
	
}

GameScreen::~GameScreen() {
	this->endBackgroundThread = true;
	this->backgroundThread.join();
	std::cout<< "GameScreen unload" <<std::endl;
}