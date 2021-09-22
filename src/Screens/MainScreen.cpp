#include "MainScreen.hpp"
#include "../Utils/Assets.hpp"
#include "../System/ScreenManager.hpp"
#include "GameScreen.hpp"

MainScreen::MainScreen() {

}

void MainScreen::update() {
	if (IsKeyPressed(KEY_ENTER)) {
		ScreenManager::changeScreen(static_cast<Screen*>(new GameScreen()));
	}
}

void MainScreen::render() {
	DrawText("Click enter to go start game", 0,0 ,20, BLACK);
}

MainScreen::~MainScreen() {

}