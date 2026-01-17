#include <raylib.h>
#include <iostream>
#include <queue>
#include "include/TextBox.h"

TextBox::TextBox(){
    active = false;
    timer = 0;
    duration = 0;
    index = -1;

    arrow = LoadTexture("sprites/objects/arrow.png");
    pigeon = LoadTexture("sprites/characters/retratoPigeon.png");
    calvo = LoadTexture("sprites/characters/retratoCalvo.png");
    teddy = LoadTexture("sprites/characters/retratoTeddy.png");
    paddy = LoadTexture("sprites/characters/retratoPaddy.png");
}

void TextBox::SetDialogue(const Dialogue& dialogue){
    multiple = dialogue.messages;
    index = 0;

    if(dialogue.character == "pigeon") retrato = pigeon;
    if(dialogue.character == "teddy") retrato = teddy;
    if(dialogue.character == "calvo") retrato = calvo;
    if(dialogue.character == "paddy") retrato = paddy;

    this->text = multiple[index];
    this->duration = dialogue.duration;
    timer = 0;
    active = true;
    size = (int) multiple.size();
}

void TextBox::EnqueuDialogue(const Dialogue& dialogue){
    dialogueQueue.push(dialogue);

    if(!active){
        SetDialogue(dialogueQueue.front());
        dialogueQueue.pop();
    }
}

void TextBox::FinishDialogue(){
    if(!dialogueQueue.empty()){
        SetDialogue(dialogueQueue.front());
        dialogueQueue.pop();
    } else{
        active = false;
    }
}

void TextBox::Update(float deltatime){
    if(!active) return;

    if(size == 1 || index == size - 1){
        timer += deltatime;
        if (timer >= duration) {
            FinishDialogue();
            return;
        }
    }

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        //for multiple words
        if(size > 1){
            index++;
            
            if(index >= size){
                FinishDialogue();
                return;
            }

            text = multiple[index];
            return;
        }
        FinishDialogue();
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