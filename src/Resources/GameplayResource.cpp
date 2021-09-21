#include "GameplayResource.hpp"
#include "../Utils/Assets.hpp"

GameplayResource::GameplayResource() {
	this->tileAtlas = LoadTexture(ASSETS_PATH"tiles.png");
}

GameplayResource::~GameplayResource() {
	UnloadTexture(tileAtlas);
}