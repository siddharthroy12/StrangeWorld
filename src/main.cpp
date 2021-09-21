#include <iostream>
#include <ctime>
#include "raylib.h"
#include "./System/ScreenManager.hpp"
#include "./System/EntitySystem.hpp"
#include "./Utils/Assets.hpp"
#include "./Screens/IntroScreen.hpp"
#include "./System/Game.hpp"
#include "./System/ResourceManager.hpp"

#define RENDER_WIDTH 1366
#define RENDER_HEIGHT 768

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

Vector2 clamp_value(Vector2 value, Vector2 min, Vector2 max) {
    Vector2 result = value;
    result.x = (result.x > max.x)? max.x : result.x;
    result.x = (result.x < min.x)? min.x : result.x;
    result.y = (result.y > max.y)? max.y : result.y;
    result.y = (result.y < min.y)? min.y : result.y;
    return result;
}

int main() {
    srand(time(0));
    //SetTraceLogLevel(LOG_NONE);
    InitWindow(0, 0, "Window title");
    
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    SetExitKey(0);
    
    RenderTexture2D renderTexture = LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT);
    SetTextureFilter(renderTexture.texture, FILTER_BILINEAR);

    EntitySystem::create(std::shared_ptr<Entity>(new Entity()));

    // Set default screen
    ScreenManager::changeScreen(std::shared_ptr<Screen>(static_cast<Screen*>(new IntroScreen())));

    while (!Game::shouldExit && !WindowShouldClose()) {
        //mousePos = GetMousePosition();
        // Compute required framebuffer scaling
        float scale = min((float)GetScreenWidth()/RENDER_WIDTH, (float)GetScreenHeight()/RENDER_HEIGHT);

        // Update virtual mouse (clamped mouse value behind game screen)
        Game::virtualMousePos.x = (GetMouseX() - (GetScreenWidth() - (RENDER_WIDTH*scale))*0.5f)/scale;
        Game::virtualMousePos.y = (GetMouseY() - (GetScreenHeight() - (RENDER_HEIGHT*scale))*0.5f)/scale;
        Game::virtualMousePos = clamp_value(Game::virtualMousePos, (Vector2){ 0, 0 }, (Vector2){ (float)RENDER_WIDTH, (float)RENDER_HEIGHT });

        
        BeginTextureMode(renderTexture);
            ClearBackground(RAYWHITE);
            ScreenManager::runScreenLoop();
        EndTextureMode();

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

    ResourceManager::unloadResources();
    CloseWindow();

    return 0;
}
