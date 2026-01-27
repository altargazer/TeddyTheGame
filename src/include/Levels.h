#ifndef LEVELS_H
#define LEVELS_H

#include <raylib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
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

    struct BadFloor{
        Rectangle area;
        Vector2 newPos;
        std::string message;
    };

    std::vector<BadFloor> badFloors;

    //from 1st level
    bool startedMission;
    int countFoods;
    std::vector<bool> foods;
    Texture2D egg, nata, flour, cheese, sugar, gas;
    Texture2D eggBig, nataBig, flourBig, cheeseBig, sugarBig, gasBig;

    //map
    Texture2D levelMap;
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
    void ManageBadFloors();
    void ControlFalling();
    void PigeonSytem(int id);
    void DrawFoods();
    void DrawBackground();
    std::vector<std::vector<int>> LoadColliders(const std::string& file);
};


#endif