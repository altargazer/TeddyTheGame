#include "include/Levels.h"
#include "include/Player.h"
#include "include/TextBox.h"
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <sstream>

/*
OBJECTS:
0: nothing
1: tile/collider
2: Weapon
3: Cocoa
4: Coco
5: Money
6: food1
7: food2
8: food3
9: food4
10:food5
11: food6
12: beds (one per level)
20-29: reserved for pigeons
*/

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}

std::vector<std::vector<int>> LoadColliders(const std::string& filename){
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

Levels::Levels(int id, Player* player, TextBox* textBox, Camera2D* camera){

    this->id = id;
    this->player = player;
    this->textBox = textBox;
    this->camera = camera;

    finished = false;

    cocoa = LoadTexture("sprites/objects/cocoa.png");
    bed = LoadTexture("sprites/objects/bed.png");
    coin = LoadTexture("sprites/objects/coinSmall.png");
    pigeon = LoadTexture("sprites/objects/pigeon.png");
    coco = LoadTexture("sprites/objects/cocoSmall.png");

    if(id == 0){
        maxDown = 576;

        levelMap = LoadTexture("sprites/maps/Level0Tileset.png");
        colliders = LoadColliders("sprites/maps/Level0.csv");

        ejecutarButton = LoadTexture("sprites/objects/ejecutar.png");

        Paddy* paddy = new Paddy({288, 230}, player, 1, textBox, 0, camera);
        enemies.push_back(paddy);
    }

    //Level 1
    else if(id == 1){
        //sprites specific to this level
        levelMap = LoadTexture("sprites/maps/Level1.png");
        background = LoadTexture("sprites/maps/Level1BG.png");
        colliders = LoadColliders("sprites/maps/Level1.csv");

        maxDown = 1216;

        weapon = LoadTexture("sprites/objects/weapon2.png");
        startedMission = false;
        countFoods = 0;
        foods = {false, false, false, false, false, false};
        eggBig = LoadTexture("sprites/objects/eggBig.png");
        sugarBig = LoadTexture("sprites/objects/sugarBig.png");
        cheeseBig = LoadTexture("sprites/objects/cheeseBig.png");
        flourBig = LoadTexture("sprites/objects/flourBig.png");
        nataBig = LoadTexture("sprites/objects/nataBig.png");
        gasBig = LoadTexture("sprites/objects/gasBig.png");

        egg = LoadTexture("sprites/objects/egg.png");
        sugar = LoadTexture("sprites/objects/sugar.png");
        cheese = LoadTexture("sprites/objects/cheese.png");
        flour = LoadTexture("sprites/objects/flour.png");
        nata = LoadTexture("sprites/objects/nata.png");
        gas = LoadTexture("sprites/objects/gas.png");
        cake = LoadTexture("sprites/objects/tarta.png");

        //add enemies here (if any)
        Paddy* paddy = new Paddy({1690, 838}, player, 1, textBox, 1, camera);
        enemies.push_back(paddy);
        MicroCalvi* calvi1 = new MicroCalvi({544, 910}, player, 416, 694);
        enemies.push_back(calvi1);
        Rata* rat1 = new Rata({416, 224+14}, player, 256, 416);
        enemies.push_back(rat1);
        Rata* rat2 = new Rata({1920, 192+14}, player, 1824, 1920);
        enemies.push_back(rat2);
        Rata* rat3 = new Rata({928, 608+14}, player, 928, 1152);
        enemies.push_back(rat3);
        Rata* rat4 = new Rata({2560, 896+14}, player, 2560, 2976);
        enemies.push_back(rat4);
        Rata* rat5 = new Rata({2848, 896+14}, player, 2560, 2976);
        enemies.push_back(rat5);
        Wall* wall1 = new Wall(1, {1312, 992}, 64, 64, player, textBox);
        enemies.push_back(wall1);

        //add bad floors here (if any)
        BadFloor clean1 = {{1696, 288, 96, 10}, {1568, 235}, "Uy, no debería pisar donde ha limpiado Paddy."};
        badFloors.push_back(clean1);
        BadFloor clean2 = {{1632, 384, 224, 10}, {1568, 235}, "Uy, no debería pisar donde ha limpiado Paddy."};
        badFloors.push_back(clean2);
        BadFloor clean3 = {{1952, 384, 224, 10}, {1568, 235}, "Uy, no debería pisar donde ha limpiado Paddy."};
        badFloors.push_back(clean3);
        BadFloor clean4 = {{2016, 128, 128, 10}, {1568, 235}, "Uy, no debería pisar donde ha limpiado Paddy."};
        badFloors.push_back(clean4);
        BadFloor hot1 = {{2976, 448, 32, 10}, {2720, 288}, "¡Ahh que me quemo!"};
        badFloors.push_back(hot1);
        BadFloor hot2 = {{2816, 512, 32, 10}, {2720, 288}, "¡Ahh que me quemo!"};
        badFloors.push_back(hot2);
        BadFloor hot3 = {{2944, 576, 64, 10}, {2720, 288}, "¡Ahh que me quemo!"};
        badFloors.push_back(hot3);
        BadFloor hot4 = {{2688, 800, 32, 10}, {2624, 608}, "¡Ahh que me quemo!"};
        badFloors.push_back(hot4);
    }

    //Level 2
    else if(id == 2){
        //max to fall
        maxDown = 1216;

        levelMap = LoadTexture("sprites/maps/Level2.png");
        background = LoadTexture("sprites/maps/Level2BG.png");
        colliders = LoadColliders("sprites/maps/Level2.csv");
    }

}

void Levels::Draw(){
    DrawTexture(levelMap, 0, 0, WHITE);
}

void Levels::DrawBackground(){
    if(id == 0){
        ClearBackground({231, 230, 226, 1});
    }
    else if(id == 1){
        DrawTexture(background, 0,0, WHITE);
        DrawTexture(background, background.width, 0, WHITE);
        DrawRectangle(0, 0, 1500, 870, Fade(WHITE, 0.5f));
    }
    else if(id == 2){
        DrawTexture(background, 0,0, WHITE);
        DrawTexture(background, background.width, 0, WHITE);
    }
}

void Levels::Update(){
    bool attacking = false;
    for(int i = 0; (std::size_t)i<enemies.size(); i++){
        if(enemies[i]->isAttacking){
            attacking = true;
        }
    }
    if(!attacking){
        player->UpgradeLevel();
    }

    ManageBadFloors();
    ControlFalling();
}

void Levels::ManageObjects(){
    for(int i = 0; i < (int)colliders.size(); i++){
        for(int j = 0; j < (int)colliders[i].size(); j++){
            int num = colliders[i][j];
            if(num != 1 && num != 0){
                float posy = i*32;
                float posx = j*32;
                DrawObject(num, posx, posy);
                //Food items and weapon are only on Level 1
                if(id == 1){
                    //Weapon
                    if(num == 2){
                        Rectangle weaponColl = {posx+4, posy+4, 24, 28};
                        if(player->HandlePickingUp(weaponColl, true)){
                            player->hasWeapon = true;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"¡Has conseguido el Palo de la Tigrosura!", "Haz click izquierdo para atacar.", "No me mates, por favor."}, "calvo"});
                        }
                    }

                    //Food Items
                    else if(num == 6){
                        Rectangle eggColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(eggColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?\nHm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[0] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"Huevos... Espero que no se me rompan por el camino."}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 7){
                        Rectangle sugarColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(sugarColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?\nHm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[1] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"El azúcar también tiene pinta de que es necesario para una rica \ntarta dulcecita."}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 8){
                        Rectangle gasColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(gasColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?\nHm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[2] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"¡Ooh, rica gasolina para echarle por encima!\nSe me haría la boca agua si tuviera glándulas salivales."}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 9){
                        Rectangle flourColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(flourColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?\nHm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[3] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"COCAINA.", "Ah no, es harina.\nPues supongo que le pondremos eso a la tarta :("}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 10){
                        Rectangle cheeseColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(cheeseColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?\nHm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[4] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"¡Queso! Igual debería darle esto a las ratas para que me dejen en paz...", "Ah claro, supongo que es más importante llevarla para hcer la tarta de queso.\nTendré que matar a las ratas, entonces."}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 11){
                        Rectangle nataColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(nataColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?\nHm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[5] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"Oh no."}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 13 && enemies[0]->condition2){
                        Rectangle cakeColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(cakeColl, true)){
                            colliders[i][j] = 0;
                            finished = true;
                        }
                    }
                }
                //cocoa: increase 1 life
                if(num == 3){
                    Rectangle cocoaColl = {posx+7, posy+14, 18, 21};
                    if(player->HandlePickingUp(cocoaColl, true)){
                        if(player->lives < 6){
                            player->lives++;
                            colliders[i][j] = 0;
                        }
                    }
                }

                //bed: update last chekpoint
                else if(num == 12){
                    Rectangle bedColl = {posx, posy, 80, 64};
                    if(player->HandlePickingUp(bedColl, true)){
                        player->lastCheckPoint = {posx+10, posy + 32};
                        player->sleeping = true;
                    }
                }

                //coin: increase player.coins
                else if(num == 5){
                    Rectangle coinColl = {posx, posy, 17, 16};
                    if(player->HandlePickingUp(coinColl, false)){
                        player->money++;
                        colliders[i][j] = 0;
                    }
                }

                //coco: inscrease player.cocos
                else if(num == 4){
                    Rectangle cocoColl = {posx, posy, 16, 15};
                    if(player->HandlePickingUp(cocoColl, true)){
                        player->cocos++;
                        textBox->EnqueuDialogue({{"Otro rico coco para Paddy."}, "teddy"});
                        colliders[i][j] = 0;
                    }
                }

                //pigeon: say something
                else if(num >= 20 && num <=29){
                    Rectangle pigeonColl = {posx, posy, 31, 28};
                    if(player->HandlePickingUp(pigeonColl, true)){
                        PigeonSytem(num-20);
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
        else if(id == 6){
            DrawTexture(egg, posX, posY+20, WHITE);
        }
        else if(id == 7){
            DrawTexture(sugar, posX, posY+20, WHITE);
        }
        else if(id == 8){
            DrawTexture(gas, posX, posY+20, WHITE);
        }
        else if(id == 9){
            DrawTexture(flour, posX, posY+20, WHITE);
        }
        else if(id == 10){
            DrawTexture(cheese, posX, posY+20, WHITE);
        }
        else if(id == 11){
            DrawTexture(nata, posX, posY+20, WHITE);
        }
        else if(id == 13 && enemies[0]->condition2){
            DrawTexture(cake, posX, posY+20, WHITE);
        }
    }
    if(id == 3){
        DrawTexture(cocoa, posX, posY + 5, WHITE);
    }
    else if(id == 4){
        DrawTexture(coco, posX, posY+17, WHITE);
    }
    else if(id == 12){
        DrawTexture(bed, posX, posY, WHITE);
    }
    else if(id == 5){
        DrawTexture(coin, posX, posY+5, WHITE);
    }
    else if(id >= 20 && id <= 29){
        DrawTexture(pigeon, posX, posY + 5, WHITE);
    }
}

void Levels::PigeonSytem(int id){
    switch (id){
        //initial
        case 0:
            textBox->EnqueuDialogue({
                {"Buenos días, Señor Teddy. Paloma #134 a su servicio.", 
                    "He sido enviada para informarle del funcionamiento de este videojuego.", 
                    "Los controles son: \n\t· A y D para moverse a izquierda y derecha. \n\t· SPACE para saltar. \n\t· E para interectuar.",
                    "Si se encuentra cansado, le recomiendo que duerma cada vez que \ntenga ocasión.\nEse será el lugar en el que reaparezca en caso de... accidente.",
                    "No olvide que la cocoa le ayudará a mantenerse sano y feliz."
                }, "pigeon"});
            textBox->EnqueuDialogue({{"Muchas gracias, soldado. Puedes descansar."}, "teddy"});
            textBox->EnqueuDialogue({{"Señor, sí, señor."}, "pigeon"});
            break;
        default:
                textBox->EnqueuDialogue({{"No tengo nada que decir."}, "pigeon"});
    }
}

void Levels::ManageEnemies(float deltatime){
    int i = 0;
    while(i < (int)enemies.size()){
        if(enemies[i]->remove){

            if(instanceof<MicroCalvi>(enemies[i])){
                player->calvis++;
            }

            //to free the memory space:
            delete enemies[i];
            //to remove the element from the vector:
            enemies.erase(enemies.begin() + i);
        } 
        else{
            enemies[i]->Update(deltatime);
            enemies[i]->Draw(deltatime);
            if(player->dead){
                enemies[i]->lives = enemies[i]->maxLives;
            }
            i++;
        }
    }
}

void Levels::ManageBadFloors(){
    for(int i = 0; i<(int)badFloors.size(); i++){
        if(CheckCollisionRecs(badFloors[i].area, player->getFeetBox())){
            player->lives--;
            if(player->lives <= 0){
                player->HandleDead();
                player->dead = true;
                return;
            }
            player->pos = badFloors[i].newPos;
            textBox->EnqueuDialogue({{badFloors[i].message}, "teddy"});
        }
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
        player->vel.y = 0;
        textBox->EnqueuDialogue({{"Upsi, me he tropezado"}, "teddy"});
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

        if(i == 0 && foods[i]){
            DrawTexture(eggBig, xpos, ypos, WHITE);
        }
        else if (i == 1 && foods[i]){
            DrawTexture(sugarBig, xpos, ypos, WHITE);
        }
        else if (i == 2 && foods[i]){
            DrawTexture(gasBig, xpos, ypos, WHITE);
        }
        else if (i == 3 && foods[i]){
            DrawTexture(flourBig, xpos, ypos, WHITE);
        }
        else if (i == 4 && foods[i]){
            DrawTexture(cheeseBig, xpos, ypos, WHITE);
        }
        else if (i == 5 && foods[i]){
            DrawTexture(nataBig, xpos, ypos, WHITE);
        }
        xpos += (10 + height-20);
    }
}

bool Levels::DrawEjecutar(){
    bool action = false;
    int btnState = 0; //0: normal, 1:hovering, 2:pressing
    float frameWidth = ejecutarButton.width/3;
    float frameHeight = ejecutarButton.height;
    Vector2 mousePoint = { 0.0f, 0.0f };
    Vector2 position = {GetScreenWidth()/2 - frameWidth/2, GetScreenHeight()/2 - frameHeight/2};
    Rectangle btnBounds = {position.x, position.y, frameWidth, frameHeight};
    Rectangle source = {0, 0, frameWidth, frameHeight};

    mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, btnBounds)){
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) action = true;
    }
    else btnState = 0;

    source.x = btnState*(ejecutarButton.width/3);

    DrawTextureRec(ejecutarButton, source, position, WHITE);
    
    return action;
}