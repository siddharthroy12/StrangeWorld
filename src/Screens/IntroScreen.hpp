#ifndef INTRO_SCREEN_HPP
#define INTRO_SCREEN_HPP

#include "./Screen.hpp"
#include "raylib.h"

class IntroScreen : Screen {
	private:
		Texture2D texture;
	public:
		IntroScreen();
		void update();
		~IntroScreen();
};

#endif