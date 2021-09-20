#include "GameScreen.hpp"
#include "../Utils/Assets.hpp"
#include "../System/ScreenManager.hpp"
#include <iostream>

GameScreen::GameScreen() {

}

void GameScreen::update() {
	DrawText("This is game screen", 0,0 ,20, BLACK);
}

GameScreen::~GameScreen() {
	std::cout<< "endme" <<std::endl;
}