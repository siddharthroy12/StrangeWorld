#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include "./Screen.hpp"
#include "../World/World.hpp"
#include "raylib.h"

class GameScreen : public Screen {
	private:
		World world;
		Camera2D camera;

	public:
		GameScreen();
		void update();
		void render();
		~GameScreen();
};

#endif