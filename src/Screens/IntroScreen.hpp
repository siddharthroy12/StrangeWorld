#ifndef INTRO_SCREEN_HPP
#define INTRO_SCREEN_HPP

#include "./Screen.hpp"
#include "raylib.h"

class IntroScreen : public Screen {
	private:
		double startTime;
	public:
		IntroScreen();
		void update();
		void render();
		~IntroScreen();
};

#endif