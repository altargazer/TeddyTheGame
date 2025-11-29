#include "include/Player.h"
#include <raylib.h>
#include <algorithm>
#include <iostream>

//Comments about sprite size:
    //Idle: 29 x 37
    //Walking: 31 x 39
    //Attack: 54 x 43
    //Life: 19 x 14

Player::Player(TextBox* textBox, float startX, float startY, int dir){
    pos = {startX, startY};
    height = 37;
    width = 29;
    speed.x = 6;
    gravity = 0.6f;
    speed.y = gravity;
    direction = dir;
    jumpPower = 12;

    lives = 4;
    money = 15;
    cocos = 5;

    this->textBox = textBox;

    isGrounded = false;
    jumping = false;
    walking = false;
    attacking = false;
    idle = true;
    wallSliding = false;

    attMaxTimer = 0.8f;

    currentAnimation = nullptr;
    currentFrame = 0;
    animationTimer = 0.0f;

    HitBox = {pos.x + 5, pos.y + 3, width - 4, height - 10};
    attackHitBox = {pos.x + width - 3, pos.y, 31, height};

    idleSheet = LoadTexture("sprites/player/PlayerIdle.png");
    walkingSheet = LoadTexture("sprites/player/PlayerWalk.png");
    attackSheet = LoadTexture("sprites/player/PlayerAttack.png");
    keyInteract = LoadTexture("sprites/objects/keyE.png");
    lifeFull = LoadTexture("sprites/objects/lifeFull.png");
    lifeEmpty = LoadTexture("sprites/objects/lifeEmpty.png");
    monedita = LoadTexture("sprites/objects/coin.png");
    coquito = LoadTexture("sprites/objects/coco.png");


    idleAnim.sheet = idleSheet;
    idleAnim.frames = 4;
    idleAnim.frameDuration = 0.3f;
    idleAnim.frameH = 37;
    idleAnim.frameW = 29;
    idleAnim.paddingRight = 1;
    idleAnim.paddingLeft = 0;
    idleAnim.paddingTop = 0;

    walkingAnim.sheet = walkingSheet;
    walkingAnim.frames = 8;
    walkingAnim.frameDuration = 0.2f;
    walkingAnim.frameH = 39;
    walkingAnim.frameW = 31;
    walkingAnim.paddingRight = 1;
    walkingAnim.paddingLeft = 2;
    walkingAnim.paddingTop = 0;

    attackAnim.sheet = attackSheet;
    attackAnim.frames = 4;
    attackAnim.frameDuration = 0.2f;
    attackAnim.frameH = 43;
    attackAnim.frameW = 54;
    attackAnim.paddingRight = 1;
    attackAnim.paddingLeft = 0;
    attackAnim.paddingTop = 6;
}

void Player::Update(float deltaTime) {

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

    //I only need padding when direction = -1
    attackAnim.paddingLeft = direction == 1 ? 0 : 25;

    if(walking || jumping || wallSliding || attacking) idle = false;
    else idle = true;

    if(walking && !attacking) ChangeAnim(&walkingAnim);
    if(idle) ChangeAnim(&idleAnim);

    if(hasWeapon) Attack(deltaTime);
    if(attacking) ChangeAnim(&attackAnim);
}

void Player::Attack(float deltaTime){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !attacking && !textBox->active) {
        attacking = true;
        attTimer = 0;
    }

    if (attacking) {
        attTimer += deltaTime;

        if (attTimer >= attMaxTimer) {
            attacking = false;
            attTimer = 0;
        }
    }
}


void Player::UpdatePositions(){
    if(direction == 1){
        HitBox = {pos.x + 5, pos.y + 3, width - 5, height - 10};
        attackHitBox = {pos.x + width - 3, pos.y, 31, height};
    } else{
        HitBox = {pos.x, pos.y + 3, width - 5, height - 10};
        attackHitBox = {pos.x - 30, pos.y, 31, height};
    }
}

void Player::Draw() {

    //source rectangle is the one we want form the sheet
    //To calculate the x of the frame: current * (frameWidth + padding)
    Rectangle sourceRec = 
        {
            (float)currentFrame*(currentAnimation->frameW + currentAnimation->paddingRight), 
            0, 
            (float)direction*currentAnimation->frameW, 
            (float)currentAnimation->frameH
        };
    
    DrawTextureRec(currentAnimation->sheet, sourceRec, {pos.x - currentAnimation->paddingLeft, pos.y - currentAnimation->paddingTop}, WHITE);

    //DrawRectangleRec(HitBox, {200, 0, 0, 100});
    //DrawRectangleRec(attackHitBox, {200, 0, 0, 100});
}

void Player::DrawTop(){
    int counter = 15;
    for(int i = 1; i <= 6; i++){
        if(lives >= i){
            DrawTexture(lifeFull, counter, 15, WHITE);
        }
        else DrawTexture(lifeEmpty, counter, 15, WHITE);
        counter += 80;
    }

    counter += 650;
    std::string coins = std::to_string(money) + "x";
    DrawText((coins.c_str()), counter, 25, 50, BLACK);
    counter += 80;
    DrawTexture(monedita, counter, 20, WHITE);

    counter += 100;
    std::string coquitos = std::to_string(cocos) + "x";
    DrawText((coquitos.c_str()), counter, 25, 50, BLACK);
    counter += 68;
    DrawTexture(coquito, counter, 22, WHITE);
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
        if(direction == 1){
            DrawTexture(keyInteract, pos.x + 25, pos.y - 7, WHITE);
        } else DrawTexture(keyInteract, pos.x - 8, pos.y - 7, WHITE);
        if(IsKeyPressed(KEY_E)){
            return true;
        }
    }
    return false;
}