#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

class Player {
public:

    //stats
    Vector2 speed;
    int jumpPower;
    Vector2 pos;
    float height, width;
    float gravity;
    int direction;

    //states
    bool isGrounded;
    bool jumping;
    bool walking;
    bool idle;
    bool wallSliding;

    //objects
    Rectangle HitBox;

    //sprites
    Texture2D idleSheet;
    Texture2D walkingSheet;
    Texture2D wallSlidingText;

    //constructors
    Player(float startX = 0, float startY = 0, int direction = 1);

    //methods
    void Update();
    void Draw();
    void JumpAndGravity();
    void HandleCollisions(Rectangle coll);
    void UpdatePositions();

};

#endif