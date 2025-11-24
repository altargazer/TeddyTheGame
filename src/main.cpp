#include <iostream>
#include <raylib.h>
#include <vector>
#include "include/Player.h"
#include "include/Levels.h"

Levels* currentLevel;
int level;

void ChangeLevel(int next, Levels* nextLevel, Player& player, int x, int y){
    level = next;
    currentLevel = nextLevel;
    player.pos = {(float)x, (float)y};
}

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Teddy: The Game");

    Player player(screenWidth / 2+50, screenHeight / 2 + 100, 1);
    Levels level1(1, &player, 96, 864);
    Levels level2(2, &player, 96, 864);

    currentLevel = &level1;
    level = 1;

    Camera2D camera = { 0 };
    camera.target = (Vector2) {player.pos.x + player.width / 2.0f, player.pos.y + player.height / 2.0f};
    camera.offset = (Vector2) {screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        player.Update();
        player.JumpAndGravity();
        player.UpdatePositions();

        if(level == 1 && currentLevel->ReachedExit(&player)){
            //ChangeLevel(2, &level2, player, 0, 0);
            std::cout << "Cambio de Nivel" << std::endl;
        }

        //Drawing Starts Here
        BeginDrawing();
        ClearBackground(WHITE);
        
        
        BeginMode2D(camera);
        
        currentLevel->Draw();
        currentLevel->ManageCollisions();

        Vector2 target = {
            player.pos.x + player.width / 2.0f,
            player.pos.y + player.height / 2.0f
        };

        camera.target.x += (target.x - camera.target.x) * 0.5f;
        camera.target.y += (target.y - camera.target.y) * 0.5f;

        float deltaTime = GetFrameTime();
        player.HandleAnimation(deltaTime);
        player.Draw();

        EndMode2D();
        EndDrawing();
    }
    
    CloseWindow();
}