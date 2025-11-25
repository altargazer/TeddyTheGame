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
    int lives;
    int money;
    int cocos;

    //states
    bool isGrounded;
    bool jumping;
    bool walking;
    bool idle;
    bool wallSliding;
    bool hasWeapon;

    //objects
    Rectangle HitBox;

    //animation
    struct Animation{
        Texture2D sheet; //sprite sheet for this animation
        int frames; //total number of frames
        float frameDuration; //duration of each frame
        int frameW; //frame width
        int frameH; //frame height
        int padding; //blanck pixels in between the frames
        int paddingLeft; //number of padding on the right for some sprites so that the position is correct
    };
    Animation walkingAnim;
    Animation idleAnim;
    Animation* currentAnimation;

    int currentFrame;
    float animationTimer;

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
    void ChangeAnim(Animation* anim);
    void HandleAnimation(float deltaTime);
    bool HandlePickingUp(Rectangle coll, bool pressing);

};

#endif