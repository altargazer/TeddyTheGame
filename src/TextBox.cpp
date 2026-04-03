#include <raylib.h>
#include <iostream>
#include <queue>
#include <sstream>
#include "include/TextBox.h"

std::string TextBox::CorrectText(std::string text){
    std::string result;
    std::stringstream ss(text);
    std::string word;
    std::string line = "";

    while(ss >> word){
        std::string newLine;
        if(line.empty()) newLine = word;
        else newLine = line + " " + word;
        if(MeasureText(newLine.c_str(), fontSize) > maxLength){
            result += line + "\n";
            line = word;
        }
        else line = newLine;
    }

    if(!line.empty()) result += line;

    return result;
}

TextBox::TextBox(){
    active = false;
    index = -1;

    maxLength = GetScreenWidth() - 20 - 250;

    arrow = LoadTexture("sprites/objects/arrow.png");
    pigeon = LoadTexture("sprites/characters/retratoPigeon.png");
    pigeonRed = LoadTexture("sprites/characters/retratoPigeonRed.png");
    pigeonBlue = LoadTexture("sprites/characters/retratoPigeonBlue.png");
    pigeonOrange = LoadTexture("sprites/characters/retratoPigeonOrange.png");
    pigeonPink = LoadTexture("sprites/characters/retratoPigeonPink.png");
    calvo = LoadTexture("sprites/characters/retratoCalvo.png");
    teddy = LoadTexture("sprites/characters/retratoTeddy.png");
    paddy = LoadTexture("sprites/characters/retratoPaddy.png");
    rat = LoadTexture("sprites/characters/retratoRatKing.png");
}

void TextBox::SetDialogue(const Dialogue& dialogue){
    multiple = dialogue.messages;
    index = 0;

    if(dialogue.character == "pigeon") retrato = pigeon;
    else if(dialogue.character == "pigeonRed") retrato = pigeonRed;
    else if(dialogue.character == "pigeonBlue") retrato = pigeonBlue;
    else if(dialogue.character == "pigeonOrange") retrato = pigeonOrange;
    else if(dialogue.character == "pigeonPink") retrato = pigeonPink;
    else if(dialogue.character == "teddy") retrato = teddy;
    else if(dialogue.character == "calvo") retrato = calvo;
    else if(dialogue.character == "paddy") retrato = paddy;
    else if(dialogue.character == "rat") retrato = rat;

    this->text = multiple[index];

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

void TextBox::Update(){
    if(!active) return;

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
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

    if(MeasureText(text.c_str(), fontSize) > maxLength){
        text = CorrectText(text);
    }

    DrawText(text.c_str(), 25 + 200, 115, fontSize, BLACK);
}