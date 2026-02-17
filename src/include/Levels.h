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
    bool interactCaja;
    char word[5];
    int letterCount;
    Rectangle textBoxPW = {750 - 570/2 + 15, 230, 570 - 40, 130 - 25};

    //Level 2
    bool startedMission;
    int countFoods;
    std::vector<bool> foods;
    Texture2D egg, nata, flour, cheese, sugar, gas, cake;
    Texture2D eggBig, nataBig, flourBig, cheeseBig, sugarBig, gasBig;

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
    void Draw();
    void DrawBackground();
    void Update();
    void ManageCollisions();
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
};


#endif