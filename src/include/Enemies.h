#ifndef ENEMIES_H
#define ENEMIES_H

#include <raylib.h>
#include "Player.h"

class Enemies{
public:

    virtual ~Enemies() {}

    //stats
    int lives;
    int damage;
    int velocity;
    int direction;
    int maxRight;
    int maxLeft;
    float deadTimer;
    Vector2 position;
    float cooldown;

    //states
    bool isAttacking;
    bool alive;
    bool remove;
    bool damaged;
 
    //objects
    Rectangle HitBox;
    Rectangle attackHitBox;
    Player* player;

    //sprites
    Texture2D idleSprite;
    Texture2D attackingSprite;
    Texture2D deadSprite;

    //animation (only for attacking)
    float frameTimer;
    float frameDuration;
    int frames;
    int padding;
    int frameW;
    int frameH;
    int currentFrame;

    virtual void Update(float deltatime);
    virtual void Draw(float deltatime);
    bool CheckCollision();
};

class MicroCalvi : public Enemies{
public:
    MicroCalvi(Vector2 pos, Player* player, int maxR, int maxL);
};

class Rata : public Enemies{
public:
    Rata(Vector2 pos, Player* player, int maxR, int maxL);
};

class Paddy : public Enemies{
public:
    TextBox* textBox;
    Paddy(Vector2 pos, Player* player, int direction, TextBox* textBox);

    void Update(float deltatime) override;
    void Draw(float deltatime) override;
};

#endif 