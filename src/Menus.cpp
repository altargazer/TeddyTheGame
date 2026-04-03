#include "include/Menus.h"
#include "include/Player.h"
#include <raylib.h>

int getMiddle(std::string text, int fontSize){
    return (GetScreenWidth()/2 - MeasureText(text.c_str(), fontSize)/2);
}

int getMiddle(std::string text, int fontSize, Font font){
    return (GetScreenWidth()/2 - MeasureTextEx(font, text.c_str(), fontSize, 3).x/2);
}

Menus::Menus(float id){
    this->id = id;

    jugarFlag = false;
    siguienteFlag = false;
    resumirFlag = false;

    if(id == 0){

    }
    else if(id == 1){
        jugar = LoadTexture("sprites/menus/start.png");
        background = LoadTexture("sprites/menus/initialScreen.png");
    }
    else if(id > 1 && (int)(id*10) % 10 == 0){
        coin = LoadTexture("sprites/objects/coin.png");
        coconut = LoadTexture("sprites/objects/coco.png");
        calvi = LoadTexture("sprites/objects/calvoHead.png");
        siguiente = LoadTexture("sprites/menus/next.png");
        salir = LoadTexture("sprites/menus/salir.png");
        background = LoadTexture("sprites/menus/bgNext.png");
    }
    else{
        interFont = LoadFontEx("fonts/04B_19.ttf", 96, 0, 250);;
        background = LoadTexture("sprites/menus/folder.png");
    }
}

void Menus::Draw(Player* player, float deltatime){
    if(id == 1){
        //DrawTexture(background, 0, 0, WHITE);
        int middle = GetScreenWidth()/2 - MeasureText("Teddy: The Game", 100)/2;
        DrawText("Teddy: The Game", middle, 100, 100, BLACK);
    }

    else if(id > 1 && (int)(id*10) % 10 == 0){

        DrawTexture(background, 0, 0, WHITE);
        DrawRectangle(0, 0, 1500, 870, Fade(WHITE, 0.5f));

        std::string top = "¡Nivel " + std::to_string((int)id - 1) + " superado!";

        DrawRectangle(getMiddle(top, 60) - 10, 70, MeasureText(top.c_str(), 60) + 20, 310, WHITE);
        DrawText(top.c_str(), getMiddle(top, 60), 80, 60, BLACK);

        //TODO añadir mensaje como atributo e imprimirlo para cada nivel
        //TODDo ponerlo todo dentro de un rectángulo blanco para que se vea bien

        std::string coins = std::to_string(player->money) + "x";
        std::string cocos = std::to_string(player->cocos) + "x";
        std::string calvis = std::to_string(player->calvis) + "x";
        int middle = GetScreenWidth()/2 - (MeasureText(coins.c_str(), 50) + coin.width +10)/2;
        DrawText(coins.c_str(), middle, 160, 50, BLACK);
        DrawTexture(coin, middle + MeasureText(coins.c_str(), 50) + 10, 155, WHITE);
        middle = GetScreenWidth()/2 - (MeasureText(cocos.c_str(), 50) + coconut.width +10)/2;
        DrawText(cocos.c_str(), middle, 240, 50, BLACK);
        DrawTexture(coconut, middle + MeasureText(cocos.c_str(), 50) + 10, 235, WHITE);
        middle = GetScreenWidth()/2 - (MeasureText(calvis.c_str(), 50) + calvi.width + 10)/2;
        DrawText(calvis.c_str(), middle, 320, 50, BLACK);
        DrawTexture(calvi, middle + MeasureText(calvis.c_str(), 50) + 10, 315, WHITE);
    }

    else if (id == 1.5){
        DrawTexture(background, 0, 0, WHITE);
        std::string line1 = "Fase 1:";
        std::string line2 = "(del Plan Ultra Secreto para\nel Objetivo Ultra Secreto del Teddy)";
        std::string line3 = "LA RED DE INFORMACION";

        DrawTextEx(interFont, line1.c_str(), (Vector2){(float)getMiddle(line1, 80, interFont), 350}, 80, 3, BLACK);
        DrawTextEx(interFont, line2.c_str(), (Vector2){(float)getMiddle(line2, 50, interFont), 430}, 50, 2, BLACK);
        DrawTextEx(interFont, line3.c_str(), (Vector2){(float)getMiddle(line3, 100, interFont), 550}, 100, 3, BLACK);
    }

    else if (id == 2.5){
        DrawTexture(background, 0, 0, WHITE);
        std::string line1 = "Fase 2:";
        std::string line2 = "(del Plan Ultra Secreto para\nel Objetivo Ultra Secreto del Teddy)";
        std::string line3 = "LOS SUMINISTROS";

        DrawTextEx(interFont, line1.c_str(), (Vector2){(float)getMiddle(line1, 80, interFont), 350}, 80, 3, BLACK);
        DrawTextEx(interFont, line2.c_str(), (Vector2){(float)getMiddle(line2, 50, interFont), 430}, 50, 2, BLACK);
        DrawTextEx(interFont, line3.c_str(), (Vector2){(float)getMiddle(line3, 100, interFont), 550}, 100, 3, BLACK);
    }
    else if (id == 3.5){
        DrawTexture(background, 0, 0, WHITE);
        std::string line1 = "Fase 3:";
        std::string line2 = "(del Plan Ultra Secreto para\nel Objetivo Ultra Secreto del Teddy)";
        std::string line3 = "EL ENEMIGO";

        DrawTextEx(interFont, line1.c_str(), (Vector2){(float)getMiddle(line1, 80, interFont), 350}, 80, 3, BLACK);
        DrawTextEx(interFont, line2.c_str(), (Vector2){(float)getMiddle(line2, 50, interFont), 430}, 50, 2, BLACK);
        DrawTextEx(interFont, line3.c_str(), (Vector2){(float)getMiddle(line3, 100, interFont), 550}, 100, 3, BLACK);
    }
}

void Menus::Update(){
    if(id == 1){
        Vector2 pos = {GetScreenWidth()/2 - (float)jugar.width/3/2, 250};
        if(DrawAndHandleBtn(jugar, pos)){
            jugarFlag = true;
        }
    }
    else if(id > 1 && (int)(id*10) % 10 == 0){
        Vector2 pos = {GetScreenWidth()/2 - (float)salir.width/3/2 - (float)siguiente.width/3/2 - 20, 400};
        if(DrawAndHandleBtn(salir, pos)){

        }
        pos = {pos.x + (float)salir.width/3 + 20, pos.y};
        if(DrawAndHandleBtn (siguiente, pos)){
            siguienteFlag = true;
        }
    }
    else{
        return;
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