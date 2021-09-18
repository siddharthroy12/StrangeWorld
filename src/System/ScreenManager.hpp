#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "../Screens/Screen.hpp"

class ScreenManager {
	private:
		Screen *currentScreen;
		bool changeScreenOnNextUpdate;
		Screen *newScreen;
	public:
	 	ScreenManager(Screen *screen);
		void runLoop();
		void changeScreen(Screen *screen);
		~ScreenManager();
};

ScreenManager::ScreenManager(Screen *screen) {
	this->currentScreen = screen;
}

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

#endif