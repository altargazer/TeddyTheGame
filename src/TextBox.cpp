#include <raylib.h>
#include <iostream>
#include "include/TextBox.h"

TextBox::TextBox(){
    active = false;
    timer = 0;
    duration = 0;
    index = -1;
}

void TextBox::Write(std::string text, float duration){
    multiple.clear();
    index = -1;

    this->text = text;
    this->duration = duration;
    timer = 0;
    active = true;
}

void TextBox::WriteMultiple(std::vector<std::string> texts){
    multiple = texts;
    index = 0;

    this->text = multiple[index];
    this->duration = 0;
    timer = 0;
    active = true;
}

void TextBox::Draw(){
    if(!active) return;

    // int width = GetScreenWidth() - 10;
    // int heigth = 100;

    DrawText(text.c_str(), 800, 550, 20, BLACK);

    //dibujar fondo caja color Fade
    //dibujar lineas caja
    //dibujar texto

    //TO-Do opción para retrato con booleano en el constructor
}

void TextBox::Update(float deltatime){
    if(!active) return;
    
    //duration = 0 for multiple, so will ignore this
    if (duration > 0) {
        timer += deltatime;
        if (timer >= duration) {
            active = false;
            return;
        }
    }

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        //for multiple
        if(index != -1){
            index++;
            
            if(index >= (int)multiple.size()){
                active = false;
                return;
            }

            text = multiple[index];
            return;
        }

        //for single
        active = false;
    }
    
}