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

void ChangeLevel(int next, Levels* nextLevel, Player& player, Vector2 newPos){
    level = next;
    currentLevel = nextLevel;
    player.pos = newPos;
    player.lastCheckPoint = newPos;
    player.direction = 1;
    player.ChangeLevel(next);
}

void ChangeMenu(float next, Menus* nextMenu, bool continueInMenu){
    menuNum = next;
    menu = continueInMenu;
    menuTimer = 0;
    currentMenu = nextMenu;
}

int main() {
    const int screenWidth = 1500;
    const int screenHeight = 870;

    InitWindow(screenWidth, screenHeight, "Teddy: El Juego");
    SetWindowState(FLAG_WINDOW_UNDECORATED);

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
    Levels level3(3, &player, &textBox, &camera);

    Menus menu1(1);
    Menus intermedio1(1.5);
    Menus menu2(2);
    Menus intermedio2(2.5);
    Menus menu3(3);
    Menus intermedio3(3.5);
    Menus menu4(4);
    
    currentLevel = &level0;
    currentMenu = &menu1;
    level = 0;
    menuNum = 1;
    menu = true;
    const int timerMenu = 5;

    const Vector2 l1 = {96, 96};
    const Vector2 l2 = {128, 947};
    const Vector2 l3 = {64, 224};

    SetTargetFPS(60);

    //ChangeLevel(3, &level3, player, l3);
    //player.hasWeapon = true;

    while (!WindowShouldClose()){
        
        float deltatime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        #pragma region Menús
        if(menu){
            currentMenu->Draw(&player, deltatime);
            currentMenu->Update();

            if(menuNum == 1 && currentMenu->jugarFlag){
                ChangeMenu(1.5, &intermedio1, false);
            }

            else if(menuNum == 1.5){
                menuTimer += deltatime;
                if(menuTimer >= timerMenu){
                    ChangeMenu(2, &menu2, false);
                }
            }

            else if(menuNum == 2 && currentMenu->siguienteFlag){
                ChangeMenu(2.5, &intermedio2, true);
            }

            else if(menuNum == 2.5){
                menuTimer += deltatime;
                if(menuTimer >= timerMenu){
                    ChangeMenu(3, &menu3, false);
                }
            }

            else if(menuNum == 3 && currentMenu->siguienteFlag){
                ChangeMenu(3.5, &intermedio3, true);
            }

            else if(menuNum == 3.5){
                menuTimer += deltatime;
                if(menuTimer >= timerMenu){
                    ChangeMenu(4, &menu4, false);
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
        
        currentLevel->Draw(deltatime);
        currentLevel->Update();
        currentLevel->ManageObjects();
        currentLevel->ManageEnemies(deltatime);
        player.Draw();

        EndMode2D();
        
        textBox.Draw();
        player.DrawTop();

        #pragma region Código de cada Nivel (fuera de cámara)
        //specific to level 0
        if(level == 0 && currentLevel->enemies[0]->condition){
            if(currentLevel->DrawEjecutar()){
                currentLevel->finished = true;
            }
        }

        //specific to level 1
        if(level == 1 && currentLevel->interactCaja){
            currentLevel->Password(deltatime);
        }

        //specific to level 2
        if(level == 2 && currentLevel->enemies[0]->initial && !currentLevel->enemies[0]->condition3){
            currentLevel->DrawFoods();
        }

        if(level == 3 && currentLevel->flagAndActive){
            currentLevel->DrawDeadFish();
        }
        #pragma endregion

        #pragma region Cambio de Nivel
        if(level == 0 && currentLevel->finished){
            menu = true;
            currentLevel->finished = false;
            ChangeLevel(1, &level1, player, l1);
        }

        else if(level == 1 && currentLevel->finished){
            menu = true;
            ChangeLevel(2, &level2, player, l2);
        }

        else if(level == 2 && currentLevel->finished){
            menu = true;
            ChangeLevel(3, &level3, player, l3);
        }

        else if(level == 3 && currentLevel->finished && !textBox.active){
            menu = true;
            //ChangeLevel(4, &level4, player, l4);
        }
        #pragma endregion

        //Position of player for development
        std::string position = "X: " + std::to_string((int)player.pos.x) + ", Y:" + std::to_string((int)(player.pos.y+player.height));
        DrawText(position.c_str(), screenWidth-200, screenHeight-40, 30, BLACK);
        
        EndDrawing();
    }
    
    CloseWindow();
}