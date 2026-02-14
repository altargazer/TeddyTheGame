#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "TextBox.h"

class Player {
public:

    //stats
    Vector2 vel;
    Vector2 pos;
    Vector2 lastCheckPoint;
    int jumpPower;
    float gravity;
    float speed;
    int direction;
    int wallDirection;
    float height, width;
    int lives, money, cocos, calvis, experience, level;
    float wallJumpTimer;
    float wallJumpDuration;

    //attack
    float attTimer;
    float attMaxTimer;
    float coolDown;
    float deadTimer;

    //states
    bool isGrounded;
    bool walking;
    bool idle;
    bool attacking;
    bool hasWeapon;
    bool damaged;
    bool dead;
    bool sleeping;
    bool wallsliding;
    bool touchingWall;

    //objects
    TextBox* textBox;
    Texture2D lifeFull;
    Texture2D lifeEmpty;
    Texture2D monedita;
    Texture2D coquito;
    std::vector<std::vector<int>> colliders;

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
    Animation deadAnim;
    Animation wallAnim;
    Animation* currentAnimation;

    int currentFrame;
    float animationTimer;

    //sprites
    Texture2D idleSheet;
    Texture2D walkingSheet;
    Texture2D attackSheet;
    Texture2D keyInteract;
    Texture2D deadSheet;
    Texture2D wallslidingSheet;

    //constructors
    Player(TextBox* textBox, float startX = 0, float startY = 0, int direction = 1);

    //methods
    void Update(float deltatime);
    void HandleInput();
    void ApplyMovement(float deltatime);
    void HandleCollisions(bool horizontal);
    void Draw();
    void ChangeAnim(Animation* anim);
    void HandleAnimation(float deltatime);
    bool HandlePickingUp(Rectangle coll, bool pressing);
    void UpgradeLevel();
    void Attack(float deltatime);
    void TakeDamage(int damage);
    void HandleDead();
    void DrawTop();
    void ChangeLevel(int level);
    Rectangle getHitBox();
    Rectangle getAttackBox();
    Rectangle getFeetBox();
    Rectangle getInteractBox();
    std::vector<std::vector<int>> LoadColliders(const std::string& filename);

};

#endif