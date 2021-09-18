#include <iostream>
#include <ctime>
#include "raylib.h"
#include "./Globals/ScreenManager.hpp"
#include "./Globals/EntitySystem.hpp"
#include "./Utils/Assets.hpp"
#include "./Globals/App.hpp"

int main() {
    srand(time(0));
    InitWindow(0, 0, "Window title");
    SetTargetFPS(60);
    SetExitKey(0);
    
    // Set default screen
    screenManager.changeScreen((Screen*) new IntroScreen());

    while (!shouldExit && !WindowShouldClose()) {
        mousePos = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        screenManager.runLoop();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
