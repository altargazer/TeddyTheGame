#include "include/Player.h"
#include <raylib.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

//Comments about sprite size:
    //Idle: 29 x 37
    //Walking: 31 x 39
    //Attack: 54 x 43
    //Life: 19 x 14

Player::Player(TextBox* textBox, float startX, float startY, int dir){
    pos = {startX, startY};
    height = 37;
    width = 29;
    speed = 300;
    gravity = 1000;
    jumpPower = 480;
    direction = dir;
    wallDirection = 0;
    coolDown = 0;
    lastCheckPoint = {startX, startY};
    experience = 0;
    level = 0;

    wallJumpDuration = 0.3f;
    wallJumpTimer = 0;

    colliders = LoadColliders("sprites/maps/Level0.csv");
    
    calvis = 0;
    lives = 6;
    money = 0;
    cocos = 0;

    this->textBox = textBox;

    isGrounded = false;
    walking = false;
    attacking = false;
    idle = true;
    damaged = false;
    dead = false;
    sleeping = false;
    wallsliding = false;
    touchingWall = false;
    frozen = false;
    swimming = false;

    attMaxTimer = 0.4f;
    deadTimer = 0;

    currentAnimation = nullptr;
    currentFrame = 0;
    animationTimer = 0.0f;

    idleSheet = LoadTexture("sprites/player/PlayerIdle.png");
    walkingSheet = LoadTexture("sprites/player/PlayerWalk.png");
    attackSheet = LoadTexture("sprites/player/PlayerAttack.png");
    deadSheet = LoadTexture("sprites/player/PlayerSleeping.png");
    wallslidingSheet = LoadTexture("sprites/player/PlayerWallSlide.png");

    keyInteract = LoadTexture("sprites/objects/keyE.png");
    lifeFull = LoadTexture("sprites/objects/lifeFull.png");
    lifeEmpty = LoadTexture("sprites/objects/lifeEmpty.png");
    monedita = LoadTexture("sprites/objects/coin.png");
    coquito = LoadTexture("sprites/objects/coco.png");

    #pragma region Animaciones
    tint = WHITE;

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
    attackAnim.frameDuration = attMaxTimer/attackAnim.frames;
    attackAnim.frameH = 43;
    attackAnim.frameW = 54;
    attackAnim.paddingRight = 1;
    attackAnim.paddingLeft = 0;
    attackAnim.paddingTop = 6;

    deadAnim.sheet = deadSheet;
    deadAnim.frames = 14;
    deadAnim.frameDuration = 0.1f;
    deadAnim.frameH = 37;
    deadAnim.frameW = 33;
    deadAnim.paddingRight = 1;
    deadAnim.paddingLeft = 0;
    deadAnim.paddingTop = 0;

    wallAnim.sheet = wallslidingSheet;
    wallAnim.frames = 1;
    wallAnim.frameDuration = 10;
    wallAnim.frameH = 40;
    wallAnim.frameW = 21;
    wallAnim.paddingRight = 0;
    wallAnim.paddingLeft = 0;
    wallAnim.paddingTop = 0;
    #pragma endregion
}

void Player::Update(float deltatime) {

    if(dead){
        deadTimer += deltatime;
        if(deadTimer >= deadAnim.frameDuration * deadAnim.frames){
            deadTimer = 0;
            dead = false;
            HandleDead();
            return;
        }
        ChangeAnim(&deadAnim);
        return;
    } 

    if(sleeping){
        deadTimer += deltatime;
        if(deadTimer >= deadAnim.frameDuration * deadAnim.frames){
            deadTimer = 0;
            sleeping = false;
            return;
        }
        ChangeAnim(&deadAnim);
        return;
    }

    if(textBox->active){
        ChangeAnim(&idleAnim);
        if(!swimming) tint = WHITE;
        return;
    }

    if(frozen) return;

    if(!swimming){
        HandleInput();
        ApplyMovement(deltatime);
        tint = WHITE;
    }
    else{
        tint = Color({143, 205, 227, 255});
        HandleInputSwimming();
        ApplyMovementSwimming(deltatime);
    }

    //I only need padding when direction = -1
    attackAnim.paddingLeft = direction == 1 ? 0 : 25;
    deadAnim.paddingLeft = direction == 1 ? 0 : 4;
    wallAnim.paddingLeft = direction == -1 ? 0 : -8;

    if(walking || attacking || wallsliding) idle = false;
    else idle = true;

    if(walking && !attacking && !wallsliding) ChangeAnim(&walkingAnim);
    if(idle) ChangeAnim(&idleAnim);

    if(hasWeapon && !wallsliding) Attack(deltatime);
    if(attacking) ChangeAnim(&attackAnim);

    if(damaged){
        coolDown += deltatime;
        if(coolDown >= 1.0f){
            coolDown = 0;
            damaged = false;
        }
    }
}

void Player::HandleInput(){
    vel.x = 0;
    walking = false;
    int inputDir = 0;
    if(IsKeyDown(KEY_D)){
        inputDir = 1;
    }
    if(IsKeyDown(KEY_A)){
        inputDir = -1;
    }

    //si wallJumping (el timer no ha llegado a cero), y se mueve hacia el pared, hacer que no se pueda mover
    if(wallJumpTimer > 0 && inputDir == wallDirection) inputDir = 0;

    vel.x = speed * inputDir;

    if(inputDir != 0){
        direction = inputDir;
        walking = true;
    } 

    if(IsKeyPressed(KEY_SPACE) && isGrounded){
        vel.y = -jumpPower;
        isGrounded = false;
    }

    if(IsKeyPressed(KEY_SPACE) && wallsliding){
        wallsliding = false;
        touchingWall = false;
        vel.y = -500;
        vel.x = 600 * -wallDirection;
        direction *= -1;
        wallJumpTimer = wallJumpDuration;
    }
}

void Player::ApplyMovement(float deltatime){
    if(wallJumpTimer > 0) wallJumpTimer -= deltatime;
    touchingWall = false;
    pos.x += vel.x * deltatime;
    HandleCollisions(true);

    vel.y += gravity*deltatime;
    if(vel.y >= 500) vel.y = 500;

    if(touchingWall && !isGrounded && vel.y > 0){
        wallsliding = true;
        ChangeAnim(&wallAnim);
        if(vel.y > 120) vel.y = 120;
    } else wallsliding = false;

    pos.y += vel.y*deltatime;
    isGrounded = false;
    HandleCollisions(false);
}

void Player::HandleInputSwimming(){
    walking = true;
    int inputDirX = 0;
    int inputDirY = 0;
    if(IsKeyDown(KEY_D)){
        inputDirX = 1;
    }
    if(IsKeyDown(KEY_A)){
        inputDirX = -1;
    }
    if(IsKeyDown(KEY_W)){
        inputDirY = -1;
    }
    if(IsKeyDown(KEY_S)){
        inputDirY = 1;
    }

    vel.x = (speed - 50) * inputDirX;
    vel.y = (speed - 50) * inputDirY;

    if(inputDirX != 0){
        direction = inputDirX;
    }
}

void Player::ApplyMovementSwimming(float deltatime){
    if(wallJumpTimer > 0) wallJumpTimer = 0;
    
    pos.x += vel.x * deltatime;
    HandleCollisions(true);

    wallsliding = false;

    pos.y += vel.y*deltatime;
    HandleCollisions(false);
}

void Player::HandleCollisions(bool horizontal){
    for(int i = 0; i < (int)colliders.size(); i++){
        for(int j = 0; j < (int)colliders[i].size(); j++){
            if(colliders[i][j] == 1){
                float posy = i*32;
                float posx = j*32;
                Rectangle tile = {posx, posy, 32, 32};
                
                if(!CheckCollisionRecs(getHitBox(), tile)) continue;

                if(horizontal){
                    touchingWall = true;
                    float overlapX = std::min(getHitBox().x + getHitBox().width, tile.x + tile.width) - std::max(getHitBox().x, tile.x);
                    if(vel.x > 0){
                        //pos.x = tile.x - getHitBox().width;
                        //para evitar tener que dibujar en otro sitio los sprites:
                        pos.x -= overlapX;
                        if(wallJumpTimer <= 0) wallDirection = 1;
                    }
                    else if(vel.x < 0){
                        //pos.x = tile.x + tile.width;
                        pos.x += overlapX;
                        if(wallJumpTimer <= 0) wallDirection = -1;
                    }
                    vel.x = 0;
                }
                else{
                    float overlapY = std::min(getHitBox().y + getHitBox().height, tile.y + tile.height) - std::max(getHitBox().y, tile.y);
                    if(vel.y > 0){
                        //pos.y = tile.y - getHitBox().height;
                        pos.y -= overlapY;
                        isGrounded = true;
                        vel.y = 0;
                        return;
                    }
                    else if(vel.y < 0){
                        //pos.y = tile.y + tile.height;
                        pos.y += overlapY;
                        vel.y = 0;
                        return;
                    }
                }
            }
        }
    }
}

void Player::Attack(float deltatime){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !attacking) {
        attacking = true;
        attTimer = 0;
    }

    if (attacking) {
        attTimer += deltatime;

        if (attTimer >= attMaxTimer) {
            attacking = false;
            attTimer = 0;
        }
    }
}

#pragma region HitBoxes
Rectangle Player::getHitBox(){
    if(direction == 1){
        return {pos.x + 5, pos.y + 3, width - 5, height - 10};
    }
    else{
        return {pos.x, pos.y + 3, width - 5, height - 10};
    }
}

Rectangle Player::getAttackBox(){
    if(direction == 1){
        return {pos.x + width - 3, pos.y, 31, height};
    }
    else{
        return {pos.x - 30, pos.y, 31, height};
    }
}

Rectangle Player::getFeetBox(){
    if(direction == 1){
        return {pos.x + 5, pos.y + height - 10, width - 10, 5};
    }
    else{
        return {pos.x + 5, pos.y + height - 10, width - 10, 5};
    }
}

Rectangle Player::getInteractBox(){
    if(direction == 1){
        return {pos.x, pos.y, width + 32, height};
    }
    else{
        return {pos.x - 32, pos.y, width + 32, height};
    }
}
#pragma endregion

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
    
    DrawTextureRec(currentAnimation->sheet, sourceRec, {pos.x - currentAnimation->paddingLeft, pos.y - currentAnimation->paddingTop}, tint);

    //DrawRectangleRec(getHitBox(), {200, 0, 0, 100});
    //DrawRectangleRec(attackHitBox, {200, 0, 0, 100});
    //DrawRectangleRec(FeetBox, RED);
}
void Player::HandleAnimation(float deltatime){
    animationTimer += deltatime;

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

void Player::UpgradeLevel(){
    if(level == 1 && experience >= 40){
        level = 2;
        textBox->teddy = LoadTexture("sprites/characters/retratoTeddyGuay.png");
        textBox->EnqueuDialogue({"¡Felicidades! Has subido al nivel 2. La foto del Teddy ha sido actualizada como recompensa"}, "calvo");
        textBox->EnqueuDialogue({"¿Qué narices signi-?"}, "teddy");
        textBox->EnqueuDialogue({"!!!"}, "teddy");
        textBox->EnqueuDialogue({"¡Toma ya, que guapo está el Teddy!"}, "teddy");
        return;
    }

    else if(level == 2 && experience >= 100){
        level = 3;
    }
}

bool Player::HandlePickingUp(Rectangle coll, bool pressing){
    if(sleeping || dead) return false;
    if(!pressing){
        return CheckCollisionRecs(getHitBox(), coll);
    }
    if (CheckCollisionRecs(getInteractBox(), coll)){
        if(direction == 1){
            DrawTexture(keyInteract, pos.x + 25, coll.y - 7, WHITE);
        } else DrawTexture(keyInteract, pos.x - 8, coll.y - 7, WHITE);
        if(IsKeyPressed(KEY_E)){
            return true;
        }
    }
    return false;
}

void Player::TakeDamage(int damage){
    if(!damaged){
        lives--;
        if(lives <= 0){
            dead = true;
            return;
        }
        damaged = true;
        pos.x -= 25*direction;
        pos.y -= 7;
    }
}

void Player::HandleDead(){
    //set dying state and change animation to sleeping, wait some seconds, then die
    lives = 6;
    pos = lastCheckPoint;
    direction = 1;
    textBox->SetDialogue({"O-oh el Teddy ha tenido una pesadilla horrible."}, "teddy");
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

    counter += 640;
    std::string coins = std::to_string(money) + "x";
    DrawText((coins.c_str()), counter, 25, 50, BLACK);
    counter += MeasureText(coins.c_str(), 50) + 10;
    DrawTexture(monedita, counter, 20, WHITE);

    counter += 100;
    std::string coquitos = std::to_string(cocos) + "x";
    DrawText((coquitos.c_str()), counter, 25, 50, BLACK);
    counter += MeasureText(coquitos.c_str(), 50) + 10;
    DrawTexture(coquito, counter, 22, WHITE);
}

void Player::ChangeLevel(int level){
    this->level = level;
    if(level == 1){
        colliders = LoadColliders("sprites/maps/Level1.csv");
    }
    else if(level == 2){
        colliders = LoadColliders("sprites/maps/Level2.csv");
    }
    else if(level == 3){
        colliders = LoadColliders("sprites/maps/Level3.csv");
    }
}

std::vector<std::vector<int>> Player::LoadColliders(const std::string& filename){
    std::vector<std::vector<int>> colliders;
    std:: ifstream file(filename);
    std::string line;
    while(std::getline(file, line)){
        std::vector<int> row;
        std::stringstream ss(line);
        std::string num;
        
        while(std::getline(ss, num, ',')){
            row.push_back(std::stoi(num));
        }

        colliders.push_back(row);
    }

    return colliders;
}