#include "GameScreen.hpp"
#include "../Utils/Assets.hpp"
#include "../System/ScreenManager.hpp"
#include "../System/ResourceManager.hpp"
#include "../Resources/GameplayResource.hpp"
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
		.zoom = 1.0f
	};

	this->pos.x = 1.0f;
	this->pos.y = 1.0f;
}

void GameScreen::backgroundThreadCallback() {
	while (!this->endBackgroundThread) {
		//std::cout << "Running" << std::endl;
		int chunkX = std::ceil(pos.x / (BLOCK_TILE_SIZE*CHUNK_SIZE_X))-1;
		int chunkY = std::ceil(pos.y / (BLOCK_TILE_SIZE*CHUNK_SIZE_Y))-1;
		
		world.loadChunk(chunkX, chunkY);

		std::vector<int> ChunksX;
		std::vector<int> ChunksY;

		for (const auto& i : world.loadedChunks) {
			if ((i.second->getPosX() != chunkX) || (i.second->getPosY() != chunkY)) {
				ChunksX.push_back(i.second->getPosX());
				ChunksY.push_back(i.second->getPosY());
				std::cout << "load" << std::endl;
			}
		}

		for (int i = 0; i < ChunksX.size(); i++) {
			world.unloadChunk(ChunksX[i], ChunksY[i]);
		}
	}
}

void GameScreen::update() {
	if (IsKeyDown(KEY_RIGHT)) {
		pos.x += 500 * GetFrameTime();
	}

	if (IsKeyDown(KEY_LEFT)) {
		pos.x -= 500 * GetFrameTime();
	}

	if (IsKeyDown(KEY_UP)) {
		pos.y -= 500 * GetFrameTime();
	}

	if (IsKeyDown(KEY_DOWN)) {
		pos.y += 500 * GetFrameTime();
	}

	camera.target = pos;

	for (const auto& i : world.loadedChunks) {
		i.second->loadTexture();
	}
}

void GameScreen::render() {
	
	//DrawText("This is game screen", 0,0 ,20, BLACK);
	int chunkX = std::ceil(pos.x / (BLOCK_TILE_SIZE*CHUNK_SIZE_X))-1;
	int chunkY = std::ceil(pos.y / (BLOCK_TILE_SIZE*CHUNK_SIZE_Y))-1;
	DrawText(TextFormat("ChunkX: %d", chunkX), 0,0, 20 , BLACK);\
	DrawText(TextFormat("ChunkY: %d", chunkY), 0,25, 20 , BLACK);

	BeginMode2D(camera);
	
	world.for_each([](std::shared_ptr<Chunk> chunk) {
		chunk->renderChunk();
	});

	DrawCircleV(pos, 10, RED);

	DrawRectangleLines(0, 0, CHUNK_SIZE_X*BLOCK_TILE_SIZE, CHUNK_SIZE_Y*BLOCK_TILE_SIZE, RED);
	
	EndMode2D();
}

GameScreen::~GameScreen() {
	this->endBackgroundThread = true;
	this->backgroundThread.join();
	std::cout<< "endme" <<std::endl;
}