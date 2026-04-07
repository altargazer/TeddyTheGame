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

    //atributos
    int id;
    Player* player;
    TextBox* textBox;
    int maxDown; //límite hasta que se puede bajar hasta morir
    Camera2D* camera;
    bool finished;
    bool initial;

    struct BadFloor{
        Rectangle area;
        Vector2 newPos;
        std::string message;
    };

    std::vector<BadFloor> badFloors;

    //Level 0
    Texture2D ejecutarButton;

    //Level 1
    Texture2D caja;
    Texture2D llave;
    bool interactCaja;
    bool open;
    char word[5];
    int letterCount;
    Rectangle textBoxPW = {750 - 570/2 + 15, 230, 570 - 40, 130 - 25};
    Texture2D pigeonRed;
    Texture2D pigeonBlue;
    Texture2D pigeonPink;
    Texture2D pigeonOrange;

    //Level 2
    bool startedMission;
    int countFoods;
    std::vector<bool> foods;
    Texture2D egg, nata, flour, cheese, sugar, gas, cake;
    Texture2D eggBig, nataBig, flourBig, cheeseBig, sugarBig, gasBig;
    Texture2D kingRat;

    //Level 3
    struct waterSpot{
        Rectangle area;
        Vector2 newPosL;
        Vector2 newPosR;
    };
    std::vector<waterSpot> waterSpots;
    Texture2D underWater;
    Texture2D wave;
    Texture2D flags, flags2, chestOpen, chestClosed, palmera, palmeraCocos;
    int currentFrameWater, numFramesWater;
    float frameTimerWater, frameDurationWater;
    int counterFishes;
    bool flag;
    bool flagAndActive;
    Texture2D deadFish;

    //Mapa
    Texture2D levelMap;
    Texture2D background;
    std::vector<std::vector<int>> colliders;

    //Objetos
    Texture2D weapon;
    Texture2D cocoa;
    Texture2D coco;
    Texture2D bed;
    Texture2D coin;
    Texture2D pigeon;

    std::vector<Enemies*> enemies;

    //methods general
    Levels(int id, Player* player, TextBox* textBox, Camera2D* camera);
    void Draw(float deltatime);
    void DrawBackground();
    void Update();
    void ManageObjects();
    void DrawObject(int id,float posX,float posY);
    void PigeonSytem(int id);
    void ManageEnemies(float deltatime);
    void ManageBadFloors();
    void ControlFalling();

    //Level 0
    bool DrawEjecutar();
    
    //Level 1
    void Password(float deltatime);

    //Level 2
    void DrawFoods();

    //Level 3
    void EnterExitWater();
    void AnimateWater(float deltatime);
    void DrawDeadFish();
};


#endif