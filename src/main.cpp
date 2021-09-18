#include "raylib.h"
#include "./Globals/EntitySystem.hpp"
#include <iostream>
#include <ctime>

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#ifndef ASSETS_PATH
#define ASSETS_PATH
#endif

int main(void)
{
    srand(time(0));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    SetTargetFPS(60);

    Texture2D texture = LoadTexture(ASSETS_PATH"test.png");


    entitySystem.create(new Entity());
    entitySystem.create(new Entity());
    entitySystem.create(new Entity());

    entitySystem.for_each([](Entity *entity) {
        std::cout << entity->_id << std::endl;
    });

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
        const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
        DrawTexture(texture, texture_x, texture_y, WHITE);

        const char* text = "OMG! IT WORKS!";
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, texture_y + texture.height + text_size.y + 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
