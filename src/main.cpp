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
float menuNum;
int level;
int fadeTimer;
float alpha;
bool menu;
float menuTimer;

void ChangeLevel(int next, Levels* nextLevel, Player& player, int x, int y){
    level = next;
    currentLevel = nextLevel;
    player.pos = {(float)x, (float)y};
    player.direction = 1;
    player.ChangeLevel(next);
}

void ChangeMenu(Menus* next, bool continueMenu){
    menuNum += 0.5;
    menu = continueMenu;
    menuTimer = 0;
    currentMenu = next;
}

int main() {
    const int screenWidth = 1500;
    const int screenHeight = 870;

    InitWindow(screenWidth, screenHeight, "Teddy: The Game");

    TextBox textBox;
    Player player(&textBox, 64, 160, 1);
    player.hasWeapon = false; //at the beggining he doesn't have the weapon

    Camera2D camera = { 0 };
    camera.target = (Vector2) {player.pos.x + player.width / 2.0f, player.pos.y + player.height / 2.0f - 20};
    camera.offset = (Vector2) {screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;

    Levels level0(0, &player, &textBox, &camera);
    Levels level1(1, &player, &textBox, &camera);
    Levels level2(2, &player, &textBox, &camera);

    Menus menu1(1);
    Menus intermedio1(1.5);
    Menus menu2(2);
    Menus intermedio2(2.5);
    Menus menu3(3);
    
    currentLevel = &level0;
    currentMenu = &menu1;
    level = 0;
    menuNum = 1;
    menu = true;

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        
        float deltatime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        #pragma region Menús
        if(menu){
            currentMenu->Draw(&player, deltatime);
            currentMenu->Update();

            if(menuNum == 1 && currentMenu->jugarFlag){
                menu = false;
                menuNum += 0.5;
                currentMenu = &intermedio1;
            }

            else if(menuNum == 1.5){
                menuTimer += deltatime;
                if(menuTimer >= 8){
                    ChangeMenu(&menu2, false);
                }
            }

            else if(menuNum == 2 && currentMenu->siguienteFlag){
                ChangeMenu(&intermedio2, true);
            }

            else if(menuNum == 2.5){
                menuTimer += deltatime;
                if(menuTimer >= 8){
                    ChangeMenu(&menu3, false);
                }
            }

            EndDrawing();
            continue;
        }
        #pragma endregion
        
        currentLevel->DrawBackground();
        
        BeginMode2D(camera);

        player.Update(deltatime);
        player.HandleAnimation(deltatime);
        textBox.Update();

        #pragma region Cámara
        Vector2 target = {
            player.pos.x + player.width / 2.0f,
            player.pos.y + player.height / 2.0f - 20
        };

        camera.target.x += (target.x - camera.target.x) * 0.5f;
        camera.target.y += (target.y - camera.target.y) * 0.5f;
        //Only way there is Pixel Perfect:
        camera.target.x = floorf(camera.target.x);
        camera.target.y = floorf(camera.target.y);
        #pragma endregion
        
        currentLevel->Draw();
        currentLevel->Update();

        currentLevel->ManageObjects();
        player.Draw();
        currentLevel->ManageEnemies(deltatime);

        EndMode2D();
        
        textBox.Draw();
        player.DrawTop();

        #pragma region Código de cada Nivel
        //specific to level 0
        if(level == 0 && currentLevel->enemies[0]->condition){
            if(currentLevel->DrawEjecutar()){
                currentLevel->finished = true;
            }
        }

        //specific to level 1
        if(level == 1 && currentLevel->enemies[0]->initial && !currentLevel->enemies[0]->condition3){
            currentLevel->DrawFoods();
        }
        #pragma endregion

        #pragma region Cambio de Nivel
        if(level == 0 && currentLevel->finished){
            menuTimer = 0;
            menu = true;
            ChangeLevel(1, &level1, player, 128, 947);
            currentLevel = &level1;
            player.lastCheckPoint = player.pos;
        }

        else if(level == 1 && currentLevel->finished){
            menu = true;
            ChangeLevel(2, &level2, player, 96, 96);
            currentLevel = &level2;
            player.lastCheckPoint = player.pos;
        }
        #pragma endregion

        //Position of player for development
        std::string position = "X: " + std::to_string((int)player.pos.x) + ", Y:" + std::to_string((int)(player.pos.y+player.height));
        DrawText(position.c_str(), screenWidth-200, screenHeight-40, 30, BLACK);
        
        EndDrawing();
    }
    
    CloseWindow();
}