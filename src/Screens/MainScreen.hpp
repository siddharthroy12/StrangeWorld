#ifndef MAIN_SCREEN_HPP
#define MAIN_SCREEN_HPP

#include "./Screen.hpp"
#include "raylib.h"

class MainScreen : public Screen {
	public:
		MainScreen();
		void update();
		~MainScreen();
};

#endif