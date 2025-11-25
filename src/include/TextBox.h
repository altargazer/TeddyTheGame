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

    TextBox();

    void Write(std::string text, float duration);
    void WriteMultiple(std::vector<std::string> texts);
    void Update(float deltatime);
    void Draw();

};

#endif