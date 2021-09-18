#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "../Screens/Screen.hpp"

class ScreenManager {
	private:
		Screen *currentScreen;
		bool changeScreenOnNextUpdate;
		Screen *newScreen;
	public:
		void runLoop();
		void changeScreen(Screen *screen);
		~ScreenManager();
};

#endif