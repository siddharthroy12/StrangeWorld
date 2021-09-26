#include <iostream>
#include <ctime>
#include <cmath>
#include "raylib.h"
#include "./System/ScreenManager.hpp"
#include "./System/EntitySystem.hpp"
#include "./Utils/Assets.hpp"
#include "./Screens/IntroScreen.hpp"
#include "./System/Game.hpp"
#include "./System/ResourceManager.hpp"
#include "./World/World.hpp"
#include "./Sizes/RenderSize.hpp"

// Get campled vector
Vector2 clamp_value(Vector2 value, Vector2 min, Vector2 max) {
    Vector2 result = value;
    result.x = (result.x > max.x)? max.x : result.x;
    result.x = (result.x < min.x)? min.x : result.x;
    result.y = (result.y > max.y)? max.y : result.y;
    result.y = (result.y < min.y)? min.y : result.y;
    return result;
}

int main() {
    srand(time(0)); // Set seed for randrom numbers
    SetTraceLogLevel(LOG_NONE); // Disable raylib loggin

    InitWindow(0, 0, "StrangeWorld"); // Create full screen window
    SetWindowState(FLAG_WINDOW_RESIZABLE); // Make window resizable
    
    SetTargetFPS(60); // Limit FPS to 60
    SetExitKey(0); // Disable escape to exit
    
    // Setup our framebuffer
    RenderTexture2D renderTexture = LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT);
    SetTextureFilter(renderTexture.texture, FILTER_BILINEAR);

    // Start with intro screen
    ScreenManager::changeScreen(static_cast<Screen*>(new IntroScreen()));

    // Game loop
    while (!Game::shouldExit && !WindowShouldClose()) {
        // Compute required framebuffer scaling
        float scale = std::min((float)GetScreenWidth()/RENDER_WIDTH, (float)GetScreenHeight()/RENDER_HEIGHT);

        // Update virtual mouse (clamped mouse value behind game screen)
        Game::virtualMousePos.x = (GetMouseX() - (GetScreenWidth() - (RENDER_WIDTH*scale))*0.5f)/scale;
        Game::virtualMousePos.y = (GetMouseY() - (GetScreenHeight() - (RENDER_HEIGHT*scale))*0.5f)/scale;
        Game::virtualMousePos = clamp_value(Game::virtualMousePos, (Vector2){ 0, 0 }, (Vector2){ (float)RENDER_WIDTH, (float)RENDER_HEIGHT });
        
        // Update current screen
        ScreenManager::updateCurrentScreen();
        
        // Render current screen to framebuffer
        BeginTextureMode(renderTexture);
            ClearBackground(RAYWHITE);
            ScreenManager::renderCurrentScreen();
        EndTextureMode();

        // Render framebuffer to screen with correct scaling
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(
			renderTexture.texture,
			(Rectangle){ 0.0f, 0.0f, (float)renderTexture.texture.width, (float)-renderTexture.texture.height },
			(Rectangle){
				(GetScreenWidth() - ((float)RENDER_WIDTH*scale))*0.5f,
				(GetScreenHeight() - ((float)RENDER_HEIGHT*scale))*0.5f,
				(float)RENDER_WIDTH*scale,
				(float)RENDER_HEIGHT*scale
			},
			(Vector2){ 0, 0 },
			0.0f,
			WHITE
		);
        EndDrawing();
    }

    // Unload necessary stuffs before closing window
    ScreenManager::unloadScreen();
    EntitySystem::unloadEntities();
    ResourceManager::unloadResources();
    World::unloadWorld();

    CloseWindow();

    // Goodbye message
    std::cout << "Hope you play again!" << std::endl;

    return 0;
}
