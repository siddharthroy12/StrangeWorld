#include "GameplayResource.hpp"
#include "../Utils/Assets.hpp"
#include <iostream>

std::string GameplayResource::_name() {
	return "GameplayResource";
}

GameplayResource::GameplayResource() {
	this->tileAtlas = LoadTexture(ASSETS_PATH"tiles.png");
	this->player = LoadTexture(ASSETS_PATH"player.png");
}

GameplayResource::~GameplayResource() {
	UnloadTexture(this->tileAtlas);
	UnloadTexture(this->player);
}