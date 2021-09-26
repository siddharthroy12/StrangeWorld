#include "IntroScreen.hpp"
#include <iostream>
#include "../Utils/Assets.hpp"
#include "../System/ScreenManager.hpp"
#include "../Sizes/RenderSize.hpp"
#include "MainScreen.hpp"

IntroScreen::IntroScreen() {
    startTime = GetTime();
}

void IntroScreen::update() {
    if (GetTime() - startTime > 1) {
        ScreenManager::changeScreen(static_cast<Screen*>(new MainScreen()));
    }
}

void IntroScreen::render() {
    const char* text1 = "MadeBy";
    const Vector2 text1Size = MeasureTextEx(GetFontDefault(), text1, 30, 1);
    const char* text2 = "Siddharth Roy";
    const Vector2 text2Size = MeasureTextEx(GetFontDefault(), text2, 50, 1);
    
    DrawText(text1, RENDER_WIDTH / 2 - text2Size.x / 2, RENDER_HEIGHT/2 - 60, 30, BLACK);
    DrawText(text2, RENDER_WIDTH / 2 - text2Size.x / 2, RENDER_HEIGHT/2 - text2Size.y / 2, 50, BLACK);
}

IntroScreen::~IntroScreen() { }