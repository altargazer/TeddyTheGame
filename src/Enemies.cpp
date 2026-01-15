#include <raylib.h>
#include <iostream>
#include <cmath>
#include "include/Enemies.h"

void Enemies::Update(float deltatime){
    if(!alive) return;
    
    isAttacking = false;

    if(player->dead) return;

    if(damaged){
        cooldown += deltatime;
        if(cooldown >= player->attMaxTimer){
            cooldown = 0;
            damaged = false;
        }
    }

    if(player->attacking && !damaged){
        if(CheckCollisionRecs(HitBox, player->attackHitBox)){
            damaged = true;
            lives--;
            position.x += 30*player->direction;
            if(lives <= 0){
                alive = false;
                return;
            } 
        }
    }

    int distanceX = player->pos.x - position.x;
    int distanceY = player->pos.y - position.y;
    if(abs(distanceX) <= 200 && abs(distanceY) <= 60){
        direction = (distanceX > 0) ? 1 : -1;
        position.x += direction*velocity;
        isAttacking = true;
    }
    if(position.x > maxRight) position.x = maxRight;
    if(position.x < maxLeft) position.x = maxLeft;

    if(CheckCollision()){
        player->TakeDamage(damage);
        position.x -= 10*direction;
    }

    HitBox = {position.x, position.y, HitBox.width, HitBox.height};
}

void Enemies::Draw(float deltatime){
    //DrawRectangleRec(HitBox, Fade(RED, 0.5));
    if(!alive){
        deadTimer += deltatime;
        if(deadTimer <= 5){
            DrawTexture(deadSprite, position.x, position.y + HitBox.height - deadSprite.height, WHITE);
        } else{
            remove = true;
        }
        return;
    }

    if(isAttacking){
        Rectangle source = {(float)currentFrame*(frameW + padding), 0, (float)frameW*direction, (float)frameH};
        DrawTextureRec(attackingSprite, source, position, WHITE);
        frameTimer += deltatime;
        if(frameTimer >= frameDuration){
            frameTimer = 0;
            currentFrame++;
            if(currentFrame >= frames) currentFrame = 0;
        }
        return;
    }
    else{
        DrawTexture(idleSprite, position.x, position.y, WHITE);
    }
}

bool Enemies::CheckCollision(){
    return (CheckCollisionRecs(HitBox, player->HitBox));
}

MicroCalvi::MicroCalvi(Vector2 pos, Player* player, int maxL, int maxR){
    //standing: 13 x 23
    //walking: 13 + 1 padding x 24
    //dead: 23 x 8

    this->player = player;

    lives = 3;
    damage = 1;
    velocity = 2;
    position = pos;
    direction = 1;
    maxRight = maxR;
    maxLeft = maxL;

    frameTimer = 0;
    frameDuration = 0.3f;
    deadTimer = 0;
    padding = 1;
    frames = 4;
    frameH = 24;
    frameW = 13;
    currentFrame = 0;

    alive = true;
    isAttacking = false;
    remove = false;
    damaged = false;

    HitBox = {position.x, position.y, 13, 23};
    idleSprite = LoadTexture("sprites/characters/microCalviAlive.png");
    attackingSprite = LoadTexture("sprites/characters/microCalviAttack.png");
    deadSprite = LoadTexture("sprites/characters/microCalviDead.png");
}

//MicroCalvi::Draw is the same as parent

Rata::Rata(Vector2 pos, Player* player, int maxL, int maxR){
    //standing: 26 x 22
    //walking: 26 + 1 padding x 22
    //dead: 

    this->player = player;

    lives = 2;
    damage = 1;
    velocity = 1.5;
    position = pos;
    direction = 1;
    maxRight = maxR;
    maxLeft = maxL;

    frameTimer = 0;
    frameDuration = 0.3f;
    deadTimer = 0;
    padding = 1;
    frames = 4;
    frameH = 22;
    frameW = 26;
    currentFrame = 0;

    alive = true;
    isAttacking = false;
    remove = false;
    damaged = false;

    HitBox = {position.x, position.y, 26, 22};
    idleSprite = LoadTexture("sprites/characters/ratAlive.png");
    attackingSprite = LoadTexture("sprites/characters/ratAttack.png");
    deadSprite = LoadTexture("sprites/characters/ratDead.png");
}

Paddy::Paddy(Vector2 pos, Player* player, int direction){

    this->player = player;

    lives = 999;
    damage = 0;
    velocity = 0;
    position = pos;
    this->direction = direction;

    frameTimer = 0;
    frameDuration = 0.3f;
    deadTimer = 0;
    padding = 1;
    frames = 2;
    frameH = 33;
    frameW = 31;
    currentFrame = 0;

    alive = true;
    isAttacking = true;
    remove = false;
    damaged = false;

    HitBox = {position.x, position.y, 31, 33};
    attackingSprite = LoadTexture("sprites/characters/PaddySheet.png");

}