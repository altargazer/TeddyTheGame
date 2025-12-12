#include <raylib.h>
#include <iostream>
#include "include/TextBox.h"

TextBox::TextBox(){
    active = false;
    timer = 0;
    duration = 0;
    index = -1;

    arrow = LoadTexture("sprites/objects/arrow.png");
    pigeon = LoadTexture("sprites/characters/retratoPigeon.png");
}

void TextBox::SetText(std::vector<std::string> message, float duration, std::string character){
    multiple = message;
    index = 0;

    if(character == "pigeon") retrato = pigeon;
    if(character == "teddy") retrato = pigeon; //Todo
    if(character == "calvo") retrato = pigeon; //Todo
    if(character == "paddy") retrato = pigeon;

    this->text = multiple[index];
    this->duration = duration;
    timer = 0;
    active = true;
    size = (int) multiple.size();
}

void TextBox::Update(float deltatime){
    if(!active) return;

    if(size == 1 || index == size - 1){
        timer += deltatime;
        if (timer >= duration) {
            active = false;
            return;
        }
    }

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        //for multiple words
        if(size > 1){
            index++;
            
            if(index >= size){
                active = false;
                return;
            }

            text = multiple[index];
            return;
        }

        active = false;
    }
    
}

void TextBox::Draw(){
    if(!active) return;

    float width = GetScreenWidth() - 20;
    float heigth = 200;

    DrawRectangle(15, 100, width, heigth, BLACK);
    DrawRectangle(10, 95, width, heigth, WHITE);
    DrawTexture(retrato, 15, 100, WHITE);
    DrawRectangleLinesEx({10, 95, width, heigth}, 2.0f, BLACK);
    
    DrawTexture(arrow, 1420, 230, WHITE);

    DrawText(text.c_str(), 25 + 200, 115, 35, BLACK);

    //TO-Do opción para retrato con booleano en el constructor
    //TO-Do flecha para avanzar
}