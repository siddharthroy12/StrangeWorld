#include "GameScreen.hpp"
#include "../Utils/Assets.hpp"
#include "../System/ScreenManager.hpp"
#include "../System/ResourceManager.hpp"
#include "../Resources/GameplayResource.hpp"
#include <iostream>
#include <memory>

GameScreen::GameScreen() {
	ResourceManager::loadResource(std::shared_ptr<Resource>(static_cast<Resource*>(new GameplayResource())));

	this->camera = (Camera2D){
		.offset = (Vector2){ 0.0f, 0.0f },
		.target = (Vector2){ 0.0f, 0.0f },
		.rotation = 0.0f,
		.zoom = 1.0f
	};
}

void GameScreen::update() {
	world.loadChunk(0,0);
}

void GameScreen::render() {
	DrawText("This is game screen", 0,0 ,20, BLACK);

	BeginMode2D(camera);
	
	world.for_each([](std::shared_ptr<Chunk> chunk) {
		chunk->renderChunk();
	});

	DrawRectangleLines(0, 0, CHUNK_SIZE_X*BLOCK_TILE_SIZE, CHUNK_SIZE_Y*BLOCK_TILE_SIZE, RED);
	
	EndMode2D();
}

GameScreen::~GameScreen() {
	std::cout<< "endme" <<std::endl;
}