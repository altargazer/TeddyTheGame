#include <iostream>
#include <raylib.h>
#include <vector>
#include <cmath>
#include "include/Player.h"
#include "include/Levels.h"
#include "include/TextBox.h"
#include "include/Enemies.h"
#include "include/Menus.h"

Levels* currentLevel;
Menus* currentMenu;
int menuNum;
int level;
int fadeTimer;
float alpha;
bool menu;

void ChangeLevel(int next, Levels* nextLevel, Player& player, int x, int y){
    level = next;
    currentLevel = nextLevel;
    player.pos = {(float)x, (float)y};
}

int main() {
    const int screenWidth = 1500;
    const int screenHeight = 870;

    InitWindow(screenWidth, screenHeight, "Teddy: The Game");

    TextBox textBox;
    Player player(&textBox, 128, 947, 1);
    player.hasWeapon = false; //at the beggining he doesn't have the weapon

    Camera2D camera = { 0 };
    camera.target = (Vector2) {player.pos.x + player.width / 2.0f, player.pos.y + player.height / 2.0f - 20};
    camera.offset = (Vector2) {screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;

    Levels level1(1, &player, &textBox, &camera);
    Levels level2(2, &player, &textBox, &camera);

    Menus menu1(1, 0);
    Menus menu2(2, 1);
    Menus menu3(3, 2);
    
    currentLevel = &level1;
    currentMenu = &menu1;
    level = 1;
    menuNum = 1;
    menu = true;

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        
        float deltatime = GetFrameTime();

        //Drawing Starts Here
        BeginDrawing();
        ClearBackground(WHITE);

        if(menu){
            currentMenu->Draw(&player);
            currentMenu->Update();

            if(menuNum == 1 && currentMenu->jugarFlag){
                menu = false;
                menuNum++;
                currentMenu = &menu2;
            }

            if(menuNum == 2 && currentMenu->siguienteFlag){
                menu = false;
                menuNum++;
                currentMenu = &menu3;
            }

            EndDrawing();
            continue;
        }
        
        currentLevel->DrawBackground();
        
        BeginMode2D(camera);

        player.Update(deltatime);
        player.JumpAndGravity();
        player.UpdatePositions();

        textBox.Update();
        
        currentLevel->Draw();
        currentLevel->Update();
        currentLevel->ManageBadFloors();
        currentLevel->ManageCollisions();
        currentLevel->ControlFalling();

        Vector2 target = {
            player.pos.x + player.width / 2.0f,
            player.pos.y + player.height / 2.0f - 20
        };

        camera.target.x += (target.x - camera.target.x) * 0.5f;
        camera.target.y += (target.y - camera.target.y) * 0.5f;
        //Only way there is Pixel Perfect:
        camera.target.x = floorf(camera.target.x);
        camera.target.y = floorf(camera.target.y);

        player.HandleAnimation(deltatime);
        currentLevel->ManageObjects();
        player.Draw();
        currentLevel->ManageEnemies(deltatime);

        EndMode2D();
        
        textBox.Draw();
        player.DrawTop();

        //specific to level 1
        if(level == 1 && currentLevel->enemies[0]->initial && !currentLevel->enemies[0]->condition3){
            currentLevel->DrawFoods();
        }

        if(level == 1 && currentLevel->finished){
            menu = true;
            ChangeLevel(2, &level2, player, 96, 96);
            currentLevel = &level2;
            player.lastCheckPoint = player.pos;
        }

        //Position of player for development
        std::string position = "X: " + std::to_string((int)player.pos.x) + ", Y:" + std::to_string((int)(player.pos.y+player.height));
        DrawText(position.c_str(), screenWidth-200, screenHeight-40, 30, BLACK);
        
        EndDrawing();
    }
    
    CloseWindow();
}