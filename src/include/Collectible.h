#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <raylib.h>
#include "Player.h"

class Collectible{
public:

    Texture2D sprite;
    bool collected;
    Player* player;
    Vector2 pos;

    Rectangle HitBox;

    Collectible(Texture2D sprite, Player* player, Vector2 pos);
    void Draw();
    void handlePickingUp();
    void onTop();

};

//Only picked up once
class Weapon : public Collectible{
public:

};

//For Level 1
class Food : public Collectible{
public:
    //When picked up, increase counter of food collected
};

//To increase 1 life
class Cocoa : public Collectible{
public:
    //Can only be picked up if lifes < maxLives
};

#endif