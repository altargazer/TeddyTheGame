#include "include/Levels.h"
#include "include/Player.h"
#include "include/TextBox.h"
#include <raylib.h>
#include <iostream>
#include <cstring>
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
13: safe (caja fuerte)
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
    initial = false;

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
        //max to fall
        maxDown = 1216;

        levelMap = LoadTexture("sprites/maps/Level1.png");
        background = LoadTexture("sprites/maps/Level1BG.png");
        colliders = LoadColliders("sprites/maps/Level1.csv");

        interactCaja = false;
        open = false;
        caja = LoadTexture("sprites/objects/caja.png");
        llave = LoadTexture("sprites/objects/llave.png");

        pigeonRed = LoadTexture("sprites/objects/pigeon1.png");
        pigeonBlue = LoadTexture("sprites/objects/pigeon2.png");
        pigeonOrange = LoadTexture("sprites/objects/pigeon3.png");
        pigeonPink = LoadTexture("sprites/objects/pigeon4.png");
    }

    //Level 2
    else if(id == 2){
        //sprites specific to this level
        levelMap = LoadTexture("sprites/maps/Level2.png");
        background = LoadTexture("sprites/maps/Level2BG.png");
        colliders = LoadColliders("sprites/maps/Level2.csv");

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

        kingRat = LoadTexture("sprites/objects/ratKing.png");

        //add enemies here (if any)
        Paddy* paddy = new Paddy({1690, 838}, player, 1, textBox, 2, camera);
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
        WallBreakable* wall1 = new WallBreakable(LoadTexture("sprites/maps/Level2Wall.png"), {1312, 992}, 64, 64, player, textBox);
        enemies.push_back(wall1);

        WallDark* wall2 = new WallDark(LoadTexture("sprites/maps/Level2DarkWall.png"), {1632, 960}, player);
        enemies.push_back(wall2);

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
    }
    else if(id == 2){
        DrawTexture(background, 0,0, WHITE);
        DrawTexture(background, background.width, 0, WHITE);
        DrawRectangle(0, 0, 1500, 870, Fade(WHITE, 0.5f));
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

    if(!initial && player->isGrounded){
        if(id == 0){
            textBox->EnqueuDialogue({{"¡Paddy!"}, "teddy"});
        }
        else if(id == 1){
            textBox->EnqueuDialogue({{"Primera fase: mi red de Información Palomar es la red de información mejor organizada y más distribuida del mundo.", "A ver que me tienen que decir."}, "teddy"});
        }
        initial = true;
    }
}

void Levels::ManageObjects(){
    for(int i = 0; i < (int)colliders.size(); i++){
        for(int j = 0; j < (int)colliders[i].size(); j++){
            int num = colliders[i][j];
            if(num != 1 && num != 0){
                float posy = i*32;
                float posx = j*32;
                DrawObject(num, posx, posy);

                if(id == 1){
                    if(num == 14){
                        if(open && !textBox->active){
                            colliders[i][j] = 15;
                            continue;
                        }
                        Rectangle cajaColl = {posx, posy, 41, 34};
                        if(player->HandlePickingUp(cajaColl, true)){
                            player->frozen = true;
                            int n = sizeof(word) / sizeof(word[0]);
                            std::fill (word, word+n, '\0');
                            letterCount = 0;
                            interactCaja = true;
                        }
                    }
                    else if(num == 15){
                        Rectangle keyColl = {posx, posy, 19, 20};
                        if(player->HandlePickingUp(keyColl, true)){
                            finished = true;
                        }
                    }
                }

                //Food items and weapon are only on Level 2
                if(id == 2){
                    //Weapon
                    if(num == 2){
                        Rectangle weaponColl = {posx+4, posy+4, 24, 28};
                        if(player->HandlePickingUp(weaponColl, true)){
                            player->hasWeapon = true;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"¡Has conseguido el Palo de la Tigrosura!", "Haz click izquierdo para atacar.", "No me mates, por favor."}, "calvo"});
                            textBox->EnqueuDialogue({{"¿Qué haces aquí, Calvi? No quiero que hables en mi juego."}, "teddy"});
                            textBox->EnqueuDialogue({{"Pero yo he programado el juego."}, "calvo"});
                            textBox->EnqueuDialogue({{"Me da igual, cállate."}, "teddy"});
                            textBox->EnqueuDialogue({{":("}, "calvo"});
                            textBox->EnqueuDialogue({{"Emoticonos tampoco."}, "teddy"});
                            textBox->EnqueuDialogue({{""}, "calvo"});
                            textBox->EnqueuDialogue({{"Muy bien."}, "teddy"});
                        }
                    }

                    //Food Items
                    else if(num == 6){
                        Rectangle eggColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(eggColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?Hm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
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
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?Hm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[1] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"El azúcar también tiene pinta de que es necesario para una rica tarta dulcecita."}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 8){
                        Rectangle gasColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(gasColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?Hm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[2] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"¡Ooh, rica gasolina para echarle por encima!Se me haría la boca agua si tuviera glándulas salivales."}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 9){
                        Rectangle flourColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(flourColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?Hm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[3] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"COCAINA.", "Ah no, es harina.Pues supongo que le pondremos eso a la tarta :("}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 10){
                        Rectangle cheeseColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(cheeseColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?Hm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[4] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"¡Queso! Igual debería darle esto a las ratas para que me dejen en paz...", "Ah claro, supongo que es más importante llevarla para hcer la tarta de queso.Tendré que matar a las ratas, entonces."}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 11){
                        Rectangle nataColl = {posx+4, posy+4, 20, 20};
                        if(player->HandlePickingUp(nataColl, true)){
                            if(!enemies[0]->initial){
                                textBox->EnqueuDialogue({{"¿Debería comerme esto?Hm, seguramente Paddy se enfadaría. Mejor no."}, "teddy"});
                                continue;
                            }
                            foods[5] = true;
                            countFoods++;
                            colliders[i][j] = 0;
                            textBox->EnqueuDialogue({{"Oh no."}, "teddy"});
                            if(countFoods == 6) enemies[0]->condition = true;
                        }
                    }
                    else if(num == 14){
                        Rectangle rat = {posx, posy+40, 20, 20};
                        if(player->HandlePickingUp(rat, true)){
                            textBox->EnqueuDialogue({{"Hola."}, "teddy"});
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
                        PigeonSytem(num);
                    }
                }
            }
        }
    }
}

void Levels::DrawObject(int id,float posX,float posY){
    if(this->id == 1){
        if(id == 14){
            DrawTexture(caja, posX, posY+5, WHITE);
        }
        else if(id == 15 && !textBox->active){
            DrawTexture(llave, posX, posY+10, WHITE);
        }
    }
    //Level 2 since it has a lot of sprites
    if(this->id == 2){
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
        else if(id == 14){
            DrawTexture(kingRat, posX, posY, WHITE);
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
        if(id == 24){
           DrawTexture(pigeonBlue, posX, posY + 5, WHITE); 
           return;
        }
        if(id == 21){
            DrawTexture(pigeonRed, posX, posY + 5, WHITE);
            return;
        }
        if(id == 28){
            DrawTexture(pigeonPink, posX, posY + 5, WHITE);
            return;
        }
        if(id == 29){
            DrawTexture(pigeonOrange, posX, posY + 5, WHITE);
            return;
        }
        DrawTexture(pigeon, posX, posY + 5, WHITE);
    }
}

void Levels::PigeonSytem(int id){
    if(id == 20){
        textBox->EnqueuDialogue({{"Hola."}, "teddy"});
        textBox->EnqueuDialogue({{"Buenos días, Señor Teddy. Paloma #1434 a su servicio."}, "pigeon"});
        textBox->EnqueuDialogue({{"Infórmame."}, "teddy"});
        textBox->EnqueuDialogue({
                {"Paloma #1434: Sí, señor, esta es la información que hemos recabado:", 
                "Paloma #1434: Las paredes han sido revisadas y hemos encontrado que puede usted deslizarse por ellas.",
                "Paloma #1434: Algunas paredes parecen estar en malas condiciones, así que tal vez pueda encontrar atajos abriendo nuevos caminos.",
                "Paloma #1434: Esté muy atento a cualquier pared o habitación con aspecto sospechoso, puede que haya algo más allá de lo que se ve a primera vista.",
                "Paloma #1434: Se han colocado diversas camas para que pueda descansar cuando lo vea necesario.Ese será el lugar en el que se encontrará en caso de... accidentes.",
                "Paloma #1434: También se han repartido reservas de cocoa por si necesita recuperarse.", 
                "Paloma #1434: El resto de mis compañeras están en sus posiciones, preparadas para observar cualquier cosa que pueda ser de interés para la operación.",
                "Paloma #1434: Eso es todo. ¿Necesita algo de más de mí, señor?"
            }, "pigeon"});
        textBox->EnqueuDialogue({{"Muchas gracias, soldado. Puedes descansar."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #1434: Señor, sí, señor."}, "pigeon"});
    }
    else if(id == 21){
        textBox->EnqueuDialogue({{"Paloma #4727: Rruu #4727 Rruu"}, "pigeonRed"});
        textBox->EnqueuDialogue({{"¿Rrruu rruu?"}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #4727: Rruuuu"}, "pigeonRed"});
        textBox->EnqueuDialogue({{"Rrruu"}, "teddy"});
    }
    else if(id == 22){
        textBox->EnqueuDialogue({{"Paloma #9344 reportando: se está \"cociendo\" una rebelión de las Ratas del Teddy en la cocina."}, "pigeon"});
        textBox->EnqueuDialogue({{"Como tu superior, te prohíbo hacer juegos de palabras que no tengan gracia."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #9344: Señor, sí, señor. Señor, lo siento, señor."}, "pigeon"});
        textBox->EnqueuDialogue({{"Me encargaré de esas ratas rebeldes, gracias por la información, soldado."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #9344: Deles su merecido, señor, la cosa está que arde."}, "pigeon"});
        textBox->EnqueuDialogue({{"Me voy a dar a la caza aviaria."}, "teddy"});
    }
    else if(id == 23){
        textBox->EnqueuDialogue({{"Señor, hola, señor. Soy Paloma #3228, encargada de RRPP (Recursos Palomos)."}, "pigeon"});
        textBox->EnqueuDialogue({{"¿Algún mensaje de parte del Grupo Palomar?", "Más os vale no montarme un motín."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #3228: Nada de eso, señor.", "Paloma #3228 Tenemos una sugerencia, señor, para nuestros números identificadores, señor.", "Paloma #3228 Creo, señor, que nuestros nombres son demasiado largos, señor.La primera cifra parece un poco innecesaria, señor."}, "pigeon"});
        textBox->EnqueuDialogue({{"Pero así estáis todas ordenadas e identificadas."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #3228: Señor, nuestros nombres los ha elegido usted de forma totalmente aleatoria, señor."}, "pigeon"});
        textBox->EnqueuDialogue({{"Ah.", "AH.", "Pequeña paloma inocente, no hables de aquellos que no conoces.", "El Teddy no hace nada de manera aleatoria, todo es parte de un plan más grande que tú que nunca podrías comprender.", "(Aunque ahora mismo no me acuerdo de qué era)."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #3228: Claro señor, siento haber subestimado el alcance de su genialidad, señor."}, "pigeon"});
        textBox->EnqueuDialogue({{"Te lo perdonaré solo por lo mucho que me haces la pelota."}, "teddy"});
    }
    else if(id == 24){
        textBox->EnqueuDialogue({{"¿Alguna cosa que reportar?"}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #5829, señor. Dato curioso: un experimento realizado en 1995 reveló que las palomas son capaces de distinguir entre las obras de Picasso y de Monet, diferenciando los estilos artísticos incluso en obras que no habían visto nunca"}, "pigeonBlue"});
        textBox->EnqueuDialogue({{"¿Vale?", "(Tal vez podría usar a las palomas para robar cuadros y luego subastarlos...)"}, "teddy"});
    }
    else if(id == 25){
        textBox->EnqueuDialogue({{"Paloma #7932: El código es 9392."}, "pigeon"});
        textBox->EnqueuDialogue({{"Podría tener algún seis..."}, "teddy"});
    }
    else if(id == 26){
        textBox->EnqueuDialogue({{"Paloma #8294: Señor, menos mal que ha llegado hasta aquí.", "Paloma #8294: Tengo una información importante: una de las palomas de esta zona es una mentirosa."}, "pigeon"});
        textBox->EnqueuDialogue({{"¿Cómo sé que no eres tú la que miente?"}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #8294: Es usted hermoso, señor."}, "pigeon"});
        textBox->EnqueuDialogue({{"Eso jamás podría ser una mentira. Buen argumento, soldado."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #8294: Gracias, señor."}, "pigeon"});
    }
    else if(id == 27){
        textBox->EnqueuDialogue({{"Por favor, dime que tienes algo de información interesante."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #4820: Claro que sí, señor, ese es mi trabajo.", "Paloma #4820: Me ha llegado la información de que el señor Paddy tiene pensado preparar una deliciosa tarta, señor."}, "pigeon"});
        textBox->EnqueuDialogue({{"Perfecto, eso es exactamente lo que el Teddy quería oír, todo va según mi plan maestro.", "Haré buen uso de esta información, gracias."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #4820: Es mi deber, señor."}, "pigeon"});
    }
    else if(id == 28){
        textBox->EnqueuDialogue({{"Paloma #1934 a su servicio, señor. Tengo un mensaje para usted."}, "pigeonPink"});
        textBox->EnqueuDialogue({{"Dímerlo ahora mismo. Ya."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #1934: El mensaje dice: \"Todo el mundo sabe que los colores del arcoíris son rosa, azul, rojo y naranja.Firmado, Teddy.\""}, "pigeonPink"});
        textBox->EnqueuDialogue({{"Entiendo.", "(No entiendo nada, qué cojones).", "Gracias por el mensaje, soldado."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #1934 : No hay de qué, señor."}, "pigeonPink"});

    }
    else if(id == 29){
        textBox->EnqueuDialogue({{"Soldado, hay una caja fuerte por ahí. ¿Tú no sabrás una combinación de cuatro dígitos?"}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #4342: Desgraciadamente no, señor, pero tengo una combinación de 22 dígitos que coinciden con la cuenta bancaria del llamado Calvi, señor.", "Paloma #4342: ¿Estaría interesado en esa información?"}, "pigeonOrange"});
        textBox->EnqueuDialogue({{"Ooh, al Teddy le interesa esa información.", "Ahora estoy ocupado con otra cosa, pero recuérdamelo más tarde."}, "teddy"});
        textBox->EnqueuDialogue({{"Paloma #4342: Señor, sí, señor."}, "pigeonOrange"});
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

void Levels::Password(float deltatime){
    DrawRectangle(750 - 570/2, 170, 570, 190, BLACK);
    DrawRectangle(750 - 570/2 + 5, 170 + 5, 570 - 10, 190 - 10, {139, 152, 184, 255});
    DrawRectangle(750 - 570/2 + 15, 230, 570 - 40, 130 - 25, {233, 237, 244, 255});

    DrawText("Introduce el código de 4 cifras:", 750 - 570/2 + 15, 170 + 15, 30, BLACK);

    int key = GetCharPressed();

    while(key > 0){
        if((key >= 48) && (key <= 57) && (letterCount < 4)){
            word[letterCount] = (char)key;
            word[letterCount+1] = '\0';
            letterCount++;
        }

        key = GetCharPressed();
    }

    if(IsKeyPressed(KEY_BACKSPACE)){
        letterCount--;
        if(letterCount < 0) letterCount = 0;
        word[letterCount] = '\0';
    }

    DrawText(word, (int)textBoxPW.x + 10, (int)textBoxPW.y + 8, 90, MAROON);

    int timer = deltatime;

    if (timer % 20 == 0){
        if (letterCount < 4){
            // Draw blinking underscore char
            DrawText("_", (int)textBoxPW.x + 13 + MeasureText(word, 90), (int)textBoxPW.y + 30, 90, MAROON);
        }
    }

    if(IsKeyPressed(KEY_ENTER)){
        std::string sol = "1454";
        bool equal = true;
        for(int i = 0; i<4; i++) if(sol[i] != word[i]) equal = false;
        if(equal){
            open = true;
            textBox->EnqueuDialogue({{"¡A la primera!", "!", "Una llave, y sé exactamente qué puertecita abre. El plan del Teddy empieza a tomar forma... Pasemos a la siguiente fase."}, "teddy"});
        }
        else{
            textBox->EnqueuDialogue({{"Esta caja está rota, no se abre >:("}, "teddy"});
        }
        player->frozen = false;
        interactCaja = false;
    }
}