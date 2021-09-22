#ifndef SCREEN_MANAGER_INSTANCE_HPP
#define SCREEN_MANAGER_INSTANCE_HPP

#include "../Screens/Screen.hpp"
#include <memory>

namespace ScreenManager {
	void renderCurrentScreen();
	void updateCurrentScreen();
	void changeScreen(std::shared_ptr<Screen> screen);
}
#endif