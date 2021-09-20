#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include "./Screen.hpp"
#include "raylib.h"

class GameScreen : public Screen {
	public:
		GameScreen();
		void update();
		~GameScreen();
};

#endif