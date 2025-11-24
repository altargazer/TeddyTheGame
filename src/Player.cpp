#include "include/Player.h"
#include <raylib.h>
#include <algorithm>
#include <iostream>

Player::Player(float startX, float startY, int dir){
    pos = {startX, startY};
    height = 37;
    width = 30;
    speed.x = 5;
    gravity = 0.6f;
    speed.y = gravity;
    direction = dir;
    jumpPower = 12;

    isGrounded = false;
    jumping = false;
    walking = false;
    idle = true;
    wallSliding = false;

    HitBox = {pos.x + 5, pos.y + 3, width - 5, height - 10};

    idleSheet = LoadTexture("sprites/player/PlayerIdle.png");
}

void Player::Update() {
    walking = false;
    isGrounded = false;
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
}

void Player::Draw() {
    Rectangle sourceRec = { 0, 0, 31, 37 }; // the one I want
    DrawTextureRec(idleSheet, sourceRec, pos, WHITE);
    DrawRectangleRec(HitBox, {200, 0, 0, 100});
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
    HitBox = {pos.x + 5, pos.y + 3, width - 5, height - 10};
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