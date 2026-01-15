#ifndef LEVELS_H
#define LEVELS_H

#include <raylib.h>
#include <vector>
#include "Player.h"
#include "TextBox.h"
#include "Enemies.h"

class Levels{
public:

    //attr
    int id;
    Player* player;
    TextBox* textBox;
    Rectangle exitRec;
    int maxDown; //limit for each limit to fall and die

    //from 1st level
    bool talkedToPaddy;

    //map
    Texture2D background;
    std::vector<std::vector<int>> colliders;

    //objects
    Texture2D weapon;
    Texture2D cocoa;
    Texture2D coco;
    Texture2D bed;
    Texture2D coin;
    Texture2D pigeon;

    //enemies
    std::vector<Enemies*> enemies;

    //methods
    Levels(int id, Player* player, TextBox* textBox, float exitX, float exitY);
    void Draw();
    void ManageCollisions();
    void ManageObjects();
    bool ReachedExit(Player* p);
    void DrawObject(int id,float posX,float posY);
    void ManageEnemies(float deltatime);
    void ControlFalling();
    void PigeonSytem(int id);
    void DrawFoods();
};


#endif