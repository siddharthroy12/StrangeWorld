#include "GameScreen.hpp"
#include "../Utils/Assets.hpp"
#include "../System/ScreenManager.hpp"
#include "../System/ResourceManager.hpp"
#include "../Resources/GameplayResource.hpp"
#include <iostream>

GameScreen::GameScreen() {
	ResourceManager::loadResource(std::shared_ptr<Resource>(static_cast<Resource*>(new GameplayResource())));
}

void GameScreen::update() {
	DrawText("This is game screen", 0,0 ,20, BLACK);
}

GameScreen::~GameScreen() {
	std::cout<< "endme" <<std::endl;
}