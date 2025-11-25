#include "include/Player.h"
#include <raylib.h>
#include <algorithm>
#include <iostream>

//Comments about sprite size:
    //Idle: 29 x 37
    //Walking: 31 x 39

Player::Player(float startX, float startY, int dir){
    pos = {startX, startY};
    height = 37;
    width = 29;
    speed.x = 6;
    gravity = 0.6f;
    speed.y = gravity;
    direction = dir;
    jumpPower = 12;

    lives = 6;
    money = 0;
    cocos = 0;

    isGrounded = false;
    jumping = false;
    walking = false;
    idle = true;
    wallSliding = false;

    currentAnimation = nullptr;
    currentFrame = 0;
    animationTimer = 0.0f;

    HitBox = {pos.x + 5, pos.y + 3, width - 4, height - 10};

    idleSheet = LoadTexture("sprites/player/PlayerIdle.png");
    walkingSheet = LoadTexture("sprites/player/PlayerWalk.png");


    idleAnim.sheet = idleSheet;
    idleAnim.frames = 4;
    idleAnim.frameDuration = 0.3f;
    idleAnim.frameH = 37;
    idleAnim.frameW = 29;
    idleAnim.padding = 1;
    idleAnim.paddingLeft = 0;

    walkingAnim.sheet = walkingSheet;
    walkingAnim.frames = 8;
    walkingAnim.frameDuration = 0.2f;
    walkingAnim.frameH = 39;
    walkingAnim.frameW = 31;
    walkingAnim.padding = 1;
    walkingAnim.paddingLeft = 2;
}

void Player::Update() {

    walking = false;
    isGrounded = false;
    wallSliding = false;

    if (IsKeyDown(KEY_D)) {
        pos.x += speed.x;
        direction = 1;
        walking = true;
    }
    if (IsKeyDown(KEY_A)) {
        pos.x -= speed.x;
        direction = -1;
        walking = true;
    }
    if (IsKeyPressed(KEY_SPACE) && !jumping) {
        speed.y = -jumpPower;
        jumping = true;
    }

    if(walking || jumping || wallSliding) idle = false;
    else idle = true;

    if(walking) ChangeAnim(&walkingAnim);
    if(idle) ChangeAnim(&idleAnim);
}

void Player::Draw() {

    //source rectangle is the one we want form the sheet
    //To calculate the x of the frame: current * (frameWidth + padding)
    Rectangle sourceRec = 
        {
            (float)currentFrame*(currentAnimation->frameW + currentAnimation->padding), 
            0, 
            (float)direction*currentAnimation->frameW, 
            (float)currentAnimation->frameH
        };
    
    DrawTextureRec(currentAnimation->sheet, sourceRec, {pos.x - currentAnimation->paddingLeft, pos.y}, WHITE);

    //DrawRectangleRec(HitBox, {200, 0, 0, 100});
}

void Player::HandleAnimation(float deltaTime){
    animationTimer += deltaTime;

    //if we have finihed time of frame
    if(animationTimer >= currentAnimation->frameDuration){
        animationTimer = 0.0f;
        currentFrame++;

        //if we have reached the last frame
        if(currentFrame >= currentAnimation->frames){
            currentFrame = 0;
        }
    }   
}

void Player::ChangeAnim(Animation* anim){
    if(currentAnimation == anim) return;

    currentAnimation = anim;
    currentFrame = 0;
    animationTimer = 0;
}

void Player::JumpAndGravity() {
    pos.y += speed.y;
    if (isGrounded) {
        speed.y = 0;
        jumping = false;
    } else {
        speed.y += gravity;
    }
}

void Player::UpdatePositions(){
    if(direction == 1){
        HitBox = {pos.x + 5, pos.y + 3, width - 5, height - 10};
    } else HitBox = {pos.x, pos.y + 3, width - 5, height - 10};
    
}

void Player::HandleCollisions(Rectangle tile){
    //Not colliding
    if (!CheckCollisionRecs(HitBox, tile)) return;

    //Calculate the overlap from every possible side
    float overlapLeft   = (HitBox.x + HitBox.width) - tile.x;
    float overlapRight  = (tile.x + tile.width) - HitBox.x;
    float overlapTop    = (HitBox.y + HitBox.height) - tile.y;
    float overlapBottom = (tile.y + tile.height) - HitBox.y;

    //Is it colliding with the tile from the left or from the right?
    float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;
    //Is it colliding with the tile from the top or from the bottom?
    float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

    //Is it horizontal or vertical?
    if (minOverlapX < minOverlapY){
        //HORIZONTAL COLLISION

        //colliding from the left
        if (overlapLeft < overlapRight){
            pos.x -= minOverlapX;
        }
        //colliding from the right
        else{ 
            pos.x += minOverlapX;
        }
        UpdatePositions();
    }
    else{
        //VERTICAL COLLISION

        //Collision from the top (ground)
        if (overlapTop < overlapBottom){
            pos.y -= minOverlapY;
            isGrounded = true;
            jumping = false;
            speed.y = 0;
        }
        //Collision from the bottom (ceiling)
        else{
            pos.y += minOverlapY;
            speed.y = 0;
        }
        UpdatePositions();
    }
}

bool Player::HandlePickingUp(Rectangle coll, bool pressing){
    if(!pressing){
        if(CheckCollisionRecs(HitBox, coll)) return true;
    }
    if (CheckCollisionRecs(HitBox, coll)){
        DrawText("Press S To Pick Up", pos.x + 35, pos.y - 10, 10, BLACK);
        if(IsKeyPressed(KEY_S)){
            return true;
        }
    }
    return false;
}