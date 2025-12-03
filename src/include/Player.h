#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "TextBox.h"

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
    float coolDown;
    Vector2 lastCheckPoint;

    //attack
    float attTimer;
    float attMaxTimer;

    //states
    bool isGrounded;
    bool jumping;
    bool walking;
    bool idle;
    bool attacking;
    bool wallSliding;
    bool hasWeapon;
    bool damaged;
    bool dead; //to do: for timer if needed

    //objects
    Rectangle HitBox;
    Rectangle attackHitBox;
    TextBox* textBox;
    Texture2D lifeFull;
    Texture2D lifeEmpty;
    Texture2D monedita;
    Texture2D coquito;

    //animation
    struct Animation{
        Texture2D sheet; //sprite sheet for this animation
        int frames; //total number of frames
        float frameDuration; //duration of each frame
        int frameW; //frame width
        int frameH; //frame height
        int paddingRight; //blanck pixels in between the frames
        int paddingLeft; //number of padding on the right for some sprites so that the position is correct
        int paddingTop; //same for the top
        
    };
    Animation walkingAnim;
    Animation idleAnim;
    Animation attackAnim;
    Animation* currentAnimation;

    int currentFrame;
    float animationTimer;

    //sprites
    Texture2D idleSheet;
    Texture2D walkingSheet;
    Texture2D wallSlidingText;
    Texture2D attackSheet;
    Texture2D keyInteract;

    //constructors
    Player(TextBox* textBox, float startX = 0, float startY = 0, int direction = 1);

    //methods
    void Update(float deltaTime);
    void Draw();
    void JumpAndGravity();
    void HandleCollisions(Rectangle coll);
    void UpdatePositions();
    void ChangeAnim(Animation* anim);
    void HandleAnimation(float deltaTime);
    void Attack(float deltaTime);
    bool HandlePickingUp(Rectangle coll, bool pressing);
    void DrawTop();
    void TakeDamage(int damage);
    void HandleDead();

};

#endif