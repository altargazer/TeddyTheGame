#include "include/Menus.h"
#include <raylib.h>

Menus::Menus(int id, int prev){
    this->id = id;
    prevLevel = prev;

    jugarFlag = false;
    siguienteFlag = false;
    resumirFlag = false;

    if(id == 0){

    }
    else if(id == 1){
        jugar = LoadTexture("sprites/menus/start.png");
    }
}

void Menus::Draw(){
    if(id == 1){
        int middle = GetScreenWidth()/2 - MeasureText("Teddy: The Game", 100)/2;
        DrawText("Teddy: The Game", middle, 100, 100, BLACK);
    }
}

void Menus::Update(){
    if(id == 1){
        Vector2 pos = {GetScreenWidth()/2 - (float)jugar.width/3/2, 250};
        if(DrawAndHandleBtn(jugar, pos)){
            jugarFlag = true;
        }
    }
}

bool Menus::DrawAndHandleBtn(Texture2D sheet, Vector2 position){
    bool action = false;
    int btnState = 0; //0: normal, 1:hovering, 2:pressing
    float frameWidth = sheet.width/3;
    float frameHeight = sheet.height;
    Vector2 mousePoint = { 0.0f, 0.0f };
    Rectangle btnBounds = {position.x, position.y, frameWidth, frameHeight};
    Rectangle source = {0, 0, frameWidth, frameHeight};

    mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, btnBounds)){
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) action = true;
    }
    else btnState = 0;

    source.x = btnState*(sheet.width/3);

    DrawTextureRec(sheet, source, position, WHITE);
    
    return action;
}