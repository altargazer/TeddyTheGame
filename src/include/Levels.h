#ifndef LEVELS_H
#define LEVELS_H

#include <raylib.h>
#include <vector>
#include "Player.h"
#include "TextBox.h"

class Levels{
public:

    //attr
    int id;
    Player* player;
    TextBox* textBox;
    Rectangle exitRec;

    //map
    Texture2D background;
    std::vector<std::vector<int>> colliders;

    //objects
    Texture2D weapon;
    Texture2D cocoa;

    //methods
    Levels(int id, Player* player, TextBox* textBox, float exitX, float exitY);
    void Draw();
    void ManageCollisions();
    void ManageObjects();
    bool ReachedExit(Player* p);
    void DrawObject(int id,float posX,float posY);

};


#endif