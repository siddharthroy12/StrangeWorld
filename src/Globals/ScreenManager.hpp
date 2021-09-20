#ifndef SCREEN_MANAGER_INSTANCE_HPP
#define SCREEN_MANAGER_INSTANCE_HPP

#include "../Screens/Screen.hpp"
#include <memory>

namespace ScreenManager {
	extern std::shared_ptr<Screen> _currentScreen;
	extern bool _changeScreenOnNextUpdate;
	extern std::shared_ptr<Screen> _newScreen;

	extern void runScreenLoop();
	extern void changeScreen(std::shared_ptr<Screen> screen);
}
#endif