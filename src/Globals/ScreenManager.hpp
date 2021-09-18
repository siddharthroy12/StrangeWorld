#ifndef SCREEN_MANAGER_INSTANCE_HPP
#define SCREEN_MANAGER_INSTANCE_HPP

#include "../System/ScreenManager.hpp"
#include "../Screens/IntroScreen.hpp"

#ifdef IMPL

ScreenManager screenManager = ScreenManager();

#else

extern ScreenManager screenManager;

#endif

#endif