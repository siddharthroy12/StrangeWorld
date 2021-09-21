#include "GameplayResource.hpp"
#include "../Utils/Assets.hpp"
#include <iostream>

GameplayResource::GameplayResource() {
	this->tileAtlas = LoadTexture(ASSETS_PATH"tiles.png");
}

GameplayResource::~GameplayResource() {
	UnloadTexture(this->tileAtlas);
	std::cout<< "done" << std::endl;
}