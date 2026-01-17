#include "include/Levels.h"
#include "include/Player.h"
#include "include/TextBox.h"
#include <raylib.h>
#include <iostream>

/*
OBJECTS:
0: nothing
1: tile/collider
2: Weapon
3: Cocoa
4: Coco
5: Money
6:
7: 
8:
9: 
10-19: reserved for beds (checkpoints)
20-29: reserved for pigeons
*/

Levels::Levels(int id, Player* player, TextBox* textBox, float exitX, float exitY){

    this->id = id;
    this->player = player;
    this->textBox = textBox;

    exitRec = {exitX, exitY, 32, 32};

    cocoa = LoadTexture("sprites/objects/cocoa.png");
    bed = LoadTexture("sprites/objects/bed.png");
    coin = LoadTexture("sprites/objects/coinSmall.png");
    pigeon = LoadTexture("sprites/objects/pigeon.png");
    coco = LoadTexture("sprites/objects/cocoSmall.png");

    //Level 1
    if(id == 1){
        //sprites specific to this level
        weapon = LoadTexture("sprites/objects/weapon2.png");
        background = LoadTexture("sprites/maps/Level1.png");

        talkedToPaddy = false;
        countFoods = 0;
        egg = LoadTexture("sprites/objects/egg.png");
        sugar = LoadTexture("sprites/objects/sugar.png");
        cheese = LoadTexture("sprites/objects/cheese.png");
        flour = LoadTexture("sprites/objects/flour.png");
        nata = LoadTexture("sprites/objects/nata.png");
        gas = LoadTexture("sprites/objects/gas.png");

        //max to fall
        maxDown = 1216;

        //colliders
        colliders = 
        {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,3,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
            {0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,10,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,20,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,1,0,0,1,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0}
        };;

        //add enemies here
        Paddy* paddy = new Paddy({1650, 838}, player, 1, textBox, 1);
        enemies.push_back(paddy);
        MicroCalvi* calvi1 = new MicroCalvi({544, 910}, player, 416, 694);
        enemies.push_back(calvi1);
        //Rata* rat1 = new Rata({1650, 845}, player, 1536, 1792);
        //enemies.push_back(rat1);
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
                            textBox->EnqueuDialogue({{"Has conseguido un arma!", "Haz click izquierdo para atacar"}, 5, "calvo"});
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
                        player->sleeping = true;
                    }
                }

                //coin: increase player.coins
                if(colliders[i][j] == 5){
                    Rectangle coinColl = {posx, posy, 17, 16};
                    if(player->HandlePickingUp(coinColl, false)){
                        player->money++;
                        colliders[i][j] = 0;
                    }
                }

                //coco: inscrease player.cocos
                if(colliders[i][j] == 4){
                    Rectangle cocoColl = {posx, posy, 16, 15};
                    if(player->HandlePickingUp(cocoColl, false)){
                        player->cocos++;
                        colliders[i][j] = 0;
                    }
                }

                //pigeon: say something
                if(colliders[i][j] >= 20 && colliders[i][j] <=29){
                    Rectangle pigeonColl = {posx, posy, 31, 28};
                    //TODO: system for different pigeons
                    if(player->HandlePickingUp(pigeonColl, true)){
                        PigeonSytem(colliders[i][j]-20);
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
    else if(id == 4){
        DrawTexture(coco, posX, posY+17, WHITE);
    }
    else if(id >= 10 && id <= 19){
        DrawTexture(bed, posX, posY, WHITE);
    }
    else if(id == 5){
        DrawTexture(coin, posX, posY+5, WHITE);
    }
    else if(id >= 20 && id <= 29){
        DrawTexture(pigeon, posX, posY + 5, WHITE);
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

void Levels::PigeonSytem(int id){
    switch (id){
        //initial
        case 0:
            textBox->EnqueuDialogue({{"Las reglas del club de la lucha son:", "Nadie habla del club de la lucha", "NADIE habla del club de la lucha", "Y no me acuerdo"}, 5, "pigeon"});
            break;

    }
}

void Levels::DrawFoods(){
    float width = GetScreenWidth() - 950;
    float height = 100;

    DrawRectangle(450, GetScreenHeight() - 120, width, height, Fade(BLACK, 0.5f));

    float xpos = 460;
    float ypos = GetScreenHeight() - 110;
    for(int i = 0; i<6; i++){
        DrawRectangleLinesEx({xpos, ypos, height-20, height-20}, 1.0f, WHITE);
        if(i == 0){
            DrawTexture(egg, xpos, ypos, WHITE);
        }
        else if (i == 1){
            DrawTexture(sugar, xpos, ypos, WHITE);
        }
        else if (i == 2){
            DrawTexture(gas, xpos, ypos, WHITE);
        }
        else if (i == 3){
            DrawTexture(flour, xpos, ypos, WHITE);
        }
        else if (i == 4){
            DrawTexture(cheese, xpos, ypos, WHITE);
        }
        else if (i == 5){
            DrawTexture(nata, xpos, ypos, WHITE);
        }
        xpos += (10 + height-20);
    }
}

void Levels::ControlFalling(){
    if(player->pos.y >= maxDown){
        player->lives--;
        if(player->lives <= 0){
            player->HandleDead();
            player->dead = true;
            return;
        }
        player->pos = player->lastCheckPoint;
        textBox->EnqueuDialogue({{"Upsi, me he tropezado"}, 5, "teddy"});
    }    
}

bool Levels::ReachedExit(Player* player){
    return CheckCollisionRecs(exitRec, player->HitBox);
}