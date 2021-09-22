#include "../Screens/Screen.hpp"
#include <memory>

namespace ScreenManager {
	Screen* _currentScreen;
	bool _changeScreenOnNextUpdate;
	Screen* _newScreen;

	void updateCurrentScreen() {
		if (_changeScreenOnNextUpdate) {
			delete _currentScreen;
			_currentScreen = _newScreen;
			_changeScreenOnNextUpdate = false;
		}

		_currentScreen->update();
	}

	void renderCurrentScreen() {
		_currentScreen->render();
	}

	void changeScreen(Screen* screen) {
		_changeScreenOnNextUpdate = true;
		_newScreen = screen;
	}

	void unloadScreen() {
		delete _currentScreen;
	}
}