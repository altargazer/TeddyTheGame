#include <raylib.h>
#include <iostream>
#include <cmath>
#include "include/Enemies.h"

void Enemies::Update(){
    if(!alive) return;
    isAttacking = false;

    int distanceX = player->pos.x - position.x;
    int distanceY = player->pos.y - position.y;
    if(abs(distanceX) <= 200 && abs(distanceY) <= 60){
        direction = (distanceX > 0) ? 1 : -1;
        position.x += direction*velocity;
        isAttacking = true;
    }
    if(position.x > maxRight) position.x = maxRight;
    if(position.x < maxLeft) position.x = maxLeft;
}

void Enemies::Draw(float deltatime){
    if(isAttacking){
        DrawTexture(attackingSprite, position.x, position.y, WHITE);
        return;
    }
    if(alive){
        DrawTexture(idleSprite, position.x, position.y, WHITE);
    }
    else{
        if(deadTimer <= 5){
            deadTimer += deltatime;
            DrawTexture(deadSprite, position.x, position.y, WHITE);
        } else remove = true;
    }
}

MicroCalvi::MicroCalvi(Vector2 pos, Player* player, int maxR, int maxL){
    //standing: 13 x 23
    //dead: 23 x 8

    this->player = player;

    lives = 2;
    damage = 1;
    velocity = 3;
    position = pos;
    direction = 1;
    maxRight = maxR;
    maxLeft = maxL;

    deadTimer = 0;

    alive = true;
    isAttacking = false;
    remove = false;

    HitBox = {position.x, position.y, 13, 23};
    idleSprite = LoadTexture("sprites/characters/microCalviAlive.png");
    attackingSprite = LoadTexture("sprites/characters/microCalviAttack.png");
    deadSprite = LoadTexture("sprites/characters/microCalviDead.png");
}

//MicroCalvi::Draw is the same as parent


