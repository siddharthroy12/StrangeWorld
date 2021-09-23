#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include "./Screen.hpp"
#include "../World/World.hpp"
#include "raylib.h"
#include <thread>

class GameScreen : public Screen {
	private:
		World world;
		Camera2D camera;
		Vector2 pos;
		std::thread backgroundThread;
		void backgroundThreadCallback();
		bool endBackgroundThread = false;
	public:
		GameScreen();
		void update();
		void render();
		~GameScreen();
};

#endif