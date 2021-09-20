#ifndef INTRO_SCREEN_HPP
#define INTRO_SCREEN_HPP

#include "./Screen.hpp"
#include "raylib.h"

class IntroScreen : public Screen {
	private:
		Texture2D texture;
		double startTime;
	public:
		IntroScreen();
		void update();
		~IntroScreen();
};

#endif