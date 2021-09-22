#include "../Screens/Screen.hpp"
#include <memory>

namespace ScreenManager {
	std::shared_ptr<Screen> _currentScreen;
	bool _changeScreenOnNextUpdate;
	std::shared_ptr<Screen> _newScreen;

	void updateCurrentScreen() {
		if (_changeScreenOnNextUpdate) {
			_currentScreen = _newScreen;
			_changeScreenOnNextUpdate = false;
		}

		_currentScreen->update();
	}

	void renderCurrentScreen() {
		_currentScreen->render();
	}

	void changeScreen(std::shared_ptr<Screen> screen) {
		_changeScreenOnNextUpdate = true;
		_newScreen = screen;
	}
}