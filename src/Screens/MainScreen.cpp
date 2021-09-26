#include "MainScreen.hpp"
#include "../Utils/Assets.hpp"
#include "../System/ScreenManager.hpp"
#include "../Sizes/RenderSize.hpp"
#include "GameScreen.hpp"

MainScreen::MainScreen() { }

void MainScreen::update() {
	if (IsKeyPressed(KEY_ENTER)) {
		ScreenManager::changeScreen(static_cast<Screen*>(new GameScreen()));
	}
}

void MainScreen::render() {
	const char *title = "StrangeWorld";
	const int titleWidth = MeasureText(title, 70);
	DrawText(title, (RENDER_WIDTH/2) - (titleWidth/2), 150, 70, BLACK);
	DrawText("Click enter to go start game", 0,0 ,20, BLACK);
}

MainScreen::~MainScreen() {

}