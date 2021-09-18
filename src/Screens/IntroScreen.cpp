#include "IntroScreen.hpp"
#include "../Utils/Assets.hpp"

IntroScreen::IntroScreen() {
	texture = LoadTexture(ASSETS_PATH"test.png");
}

void IntroScreen::update() {
	const int texture_x = GetScreenWidth() / 2 - texture.width / 2;
    const int texture_y = GetScreenHeight() / 2 - texture.height / 2;
    DrawTexture(texture, texture_x, texture_y, WHITE);

	const char* text = "OMG! IT WORKS!";
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, GetScreenWidth() / 2 - text_size.x / 2, texture_y + texture.height + text_size.y + 10, 20, BLACK);
}

IntroScreen::~IntroScreen() {

}