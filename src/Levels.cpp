#include "include/Levels.h"
#include "include/Player.h"
#include "include/TextBox.h"
#include <raylib.h>
#include <iostream>

/*
OBJECTS:
0: nothing
1: tile/collider
2: 
3: Cocoa
4: Coco
5: Money
6: 
7: 
8:
9: 
10-19: reserved for beds (checkpoints)
*/

Levels::Levels(int id, Player* player, TextBox* textBox, float exitX, float exitY){

    this->id = id;
    this->player = player;
    this->textBox = textBox;

    exitRec = {exitX, exitY, 32, 32};

    cocoa = LoadTexture("sprites/objects/cocoa.png");
    bed = LoadTexture("sprites/objects/bed.png");

    //Level 1
    if(id == 1){
        //sprites specific to this level
        weapon = LoadTexture("sprites/objects/weapon2.png");
        background = LoadTexture("sprites/maps/Level1.png");

        //max to fall
        maxDown = 1216;

        //colliders
        colliders = 
        {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
            {0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,10,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,1,0,0,1,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0}
        };;

        //add enemies here
        MicroCalvi* calvi1 = new MicroCalvi({544, 910}, player, 694, 416);
        enemies.push_back(calvi1);
    }

    //Level 2
    if(id == 2){
        
    }

}

void Levels::Draw(){
    DrawTexture(background, 0, 0, WHITE);
}

void Levels::ManageCollisions(){
    for(int i = 0; i < (int)colliders.size(); i++){
        for(int j = 0; j < (int)colliders[i].size(); j++){
            if(colliders[i][j] == 1){
                float posy = i*32;
                float posx = j*32;
                Rectangle plat = {posx, posy, 32, 32};
                //DrawRectangleRec(plat, semi_transparent);
                player->HandleCollisions(plat);
            }
        }
    }
}

void Levels::ManageObjects(){
    for(int i = 0; i < (int)colliders.size(); i++){
        for(int j = 0; j < (int)colliders[i].size(); j++){
            if(colliders[i][j] != 1 && colliders[i][j] != 0){
                float posy = i*32;
                float posx = j*32;
                DrawObject(colliders[i][j], posx, posy);
                //Food items and weapon are only on Level 1
                if(id == 1){
                    //Weapon
                    if(colliders[i][j] == 2){
                        Rectangle weaponColl = {posx+4, posy+4, 24, 28};
                        if(player->HandlePickingUp(weaponColl, true)){
                            player->hasWeapon = true;
                            colliders[i][j] = 0;
                            textBox->SetText({"Has conseguido un arma!", "Haz click izquierdo para atacar"}, 5);
                        }
                    }

                    //Food Items TO-DO
                }
                //cocoa: increase 1 life
                if(colliders[i][j] == 3){
                    Rectangle cocoaColl = {posx+7, posy+14, 18, 21};
                    if(player->HandlePickingUp(cocoaColl, true)){
                        if(player->lives < 6){
                            player->lives++;
                            colliders[i][j] = 0;
                        }
                    }
                }

                //bed: update last chekpoint
                if(colliders[i][j] >= 10 && colliders[i][j] <=19){
                    Rectangle bedColl = {posx, posy, 80, 64};
                    if(player->HandlePickingUp(bedColl, true)){
                        player->lastCheckPoint = {posx+10, posy + 32};
                        std::cout << "Nuevo check point: " << player->lastCheckPoint.x << ", " << player->lastCheckPoint.y << std::endl;
                    }
                }
            }
        }
    }
}

void Levels::DrawObject(int id,float posX,float posY){
    //Level 1 since it has a lot of sprites
    if(this->id == 1){
        if(id == 2){
            DrawTexture(weapon, posX, posY+5, WHITE);
        }
    }
    if(id == 3){
        DrawTexture(cocoa, posX, posY + 5, WHITE);
    }
    else if(id >= 10 && id <= 19){
        DrawTexture(bed, posX, posY, WHITE);
    }
}

void Levels::ManageEnemies(float deltatime){
    int i = 0;
    while(i < (int)enemies.size()){
        if(enemies[i]->remove){
            //to free the memory space:
            delete enemies[i];
            //to remove the element from the vector:
            enemies.erase(enemies.begin() + i);
        } 
        else{
            enemies[i]->Update(deltatime);
            enemies[i]->Draw(deltatime);
            i++;
        }
    }
}

void Levels::ControlFalling(){
    if(player->pos.y >= maxDown){
        player->lives--;
        if(player->lives <= 0){
            player->HandleDead();
            return;
        }
        player->pos = player->lastCheckPoint;
        textBox->SetText({"Upsi, me he tropezado"}, 5);
    }    
}

bool Levels::ReachedExit(Player* player){
    return CheckCollisionRecs(exitRec, player->HitBox);
}