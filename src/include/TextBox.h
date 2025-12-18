#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <raylib.h>
#include <iostream>
#include <vector>

class TextBox{
public:

    std::string text;
    std::vector<std::string> multiple;
    bool active;
    float timer;
    float duration; //time that it lasts if not clicked
    int index; //index for multiple messages
    int size;

    Texture2D arrow;
    Texture2D retrato;
    Texture2D pigeon;
    Texture2D calvo;
    Texture2D paddy;
    Texture2D teddy;

    TextBox();

    void SetText(std::vector<std::string> message, float duration, std::string character);
    void Update(float deltatime);
    void Draw();

};

#endif