#ifndef ENEMIES_H
#define ENEMIES_H

#include <raylib.h>
#include "Player.h"

class Enemies{
public:

    virtual ~Enemies(){}

    //stats
    int lives;
    int maxLives;
    int damage;
    int velocity;
    int direction;
    int maxRight;
    int maxLeft;
    float deadTimer;
    Vector2 position;
    float cooldown;
    int experience;

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

    //paddy
    bool initial;
    bool condition;
    bool condition2;
    bool condition3;

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
    Camera2D* camera;
    int level;

    //in the first level, the condition is to get all the ingridients
    Paddy(Vector2 pos, Player* player, int direction, TextBox* textBox, int level, Camera2D* camera);

    void Update(float deltatime) override;
    void Draw(float deltatime) override;
    void FadeBlack(float deltatime);
};

class Wall : public Enemies{
public:

    TextBox* textBox;

    Texture2D sheet;
    Rectangle normal;
    Rectangle broken1;
    Rectangle broken2;

    Wall(float level, Vector2 pos, int height, int width, Player* player, TextBox* textBox);
    void Draw(float deltatime) override;
    void Update(float deltatime) override;
};

#endif 