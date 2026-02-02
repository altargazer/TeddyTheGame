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