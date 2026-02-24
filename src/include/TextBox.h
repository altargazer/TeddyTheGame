#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <raylib.h>
#include <iostream>
#include <vector>
#include <queue>

class TextBox{
public:

    std::string text;
    std::vector<std::string> multiple;
    bool active;
    int index; //index for multiple messages
    int size;

    Texture2D arrow;
    Texture2D retrato;
    Texture2D pigeon;
    Texture2D pigeonRed;
    Texture2D pigeonBlue;
    Texture2D pigeonOrange;
    Texture2D pigeonPink;
    Texture2D calvo;
    Texture2D paddy;
    Texture2D teddy;

    struct Dialogue{
        std::vector<std::string> messages;
        std::string character;
    };

    std::queue<Dialogue> dialogueQueue;

    TextBox();

    void SetDialogue(const Dialogue& dialogue);
    void EnqueuDialogue(const Dialogue& dialogue);
    void FinishDialogue();
    void Update();
    void Draw();

};

#endif