#include "MainScreen.hpp"
#include "../Utils/Assets.hpp"
#include "../Globals/ScreenManager.hpp"
#include "GameScreen.hpp"

MainScreen::MainScreen() {

}

void MainScreen::update() {
	DrawText("Click enter to go start game", 0,0 ,20, BLACK);

	if (IsKeyPressed(KEY_ENTER)) {
		ScreenManager::changeScreen(std::shared_ptr<Screen>(static_cast<Screen*>(new GameScreen())));
	}
}

MainScreen::~MainScreen() {

}