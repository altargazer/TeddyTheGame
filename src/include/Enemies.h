#ifndef ENEMIES_H
#define ENEMIES_H

#include <raylib.h>
#include "PLayer.h"

class Enemies{
public:
    //stats
    int lives;
    int damage;
    int velocity;
    int direction;
    int maxRight;
    int maxLeft;
    float deadTimer;
    Vector2 position;

    //states
    bool isAttacking;
    bool alive;
    bool remove;
 
    //objects
    Rectangle HitBox;
    Rectangle attackHitBox;
    Player* player;

    //sprites
    Texture2D idleSprite;
    Texture2D attackingSprite;
    Texture2D deadSprite;

    void Update();
    void Draw(float deltatime);
};

class MicroCalvi : public Enemies{
public:
    MicroCalvi(Vector2 pos, Player* player, int maxR, int maxL);
};

class Rata : public Enemies{
public:
    Rata(Vector2 pos);
};

#endif 