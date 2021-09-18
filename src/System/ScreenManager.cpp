#include "ScreenManager.hpp"

void ScreenManager::runLoop() {
	if (this->changeScreenOnNextUpdate) {
		delete currentScreen;
		this->currentScreen = newScreen;
		this->changeScreenOnNextUpdate = false;
	}

	this->currentScreen->update();
}

void ScreenManager::changeScreen(Screen *screen) {
	this->changeScreenOnNextUpdate = true;
	this->newScreen = screen;
}

ScreenManager::~ScreenManager() {
	delete currentScreen;
}