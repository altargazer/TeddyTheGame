#include <raylib.h>
#include <iostream>
#include "include/Collectible.h"
#include "include/Player.h"

Collectible::Collectible(Texture2D sprite, Player* player, Vector2 pos){
    this->sprite = sprite;
    this->player = player;
    this->pos = pos;

    HitBox = {pos.x, pos.y, (float)sprite.width, (float)sprite.height};

    collected = false;
}

void Collectible::handlePickingUp(){

}

void Collectible::onTop(){
    if(CheckCollisionRecs(player->HitBox, this->HitBox)){
        //show message that you can pick it up pressing E
        std::cout << "You can pick this object up" << std::endl;
    }
}