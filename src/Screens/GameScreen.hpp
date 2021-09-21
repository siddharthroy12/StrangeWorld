#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include "./Screen.hpp"
#include "../World/World.hpp"
#include "raylib.h"

class GameScreen : public Screen {
	private:
		World world;

	public:
		GameScreen();
		void update();
		~GameScreen();
};

#endif