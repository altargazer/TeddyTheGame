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
                player->experience += experience;
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

    if(CheckCollisionRecs(player->HitBox, HitBox)){
        player->TakeDamage(damage);
        position.x -= 10*direction;
    }

    HitBox = {position.x, position.y, HitBox.width, HitBox.height};
}

void Enemies::Draw(float deltatime){
    //DrawRectangleRec(HitBox, Fade(RED, 0.5));
    if(!alive){
        deadTimer += deltatime;
        if(deadTimer <= 2){
            std::string exp = "+" + std::to_string(experience) + " exp.";
            DrawText(exp.c_str(), player->pos.x, player->pos.y -15, 10, GREEN);
        }
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
    maxLives = 3;
    damage = 1;
    velocity = 2;
    position = pos;
    direction = 1;
    maxRight = maxR;
    maxLeft = maxL;
    experience = 20;

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
    maxLives = 2;
    damage = 1;
    velocity = 1.5;
    position = pos;
    direction = 1;
    maxRight = maxR;
    maxLeft = maxL;
    experience = 10;

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

Paddy::Paddy(Vector2 pos, Player* player, int direction, TextBox* textBox, int level, Camera2D* camera){
    this->player = player;
    this->textBox = textBox;
    this->level = level;
    this->camera = camera;

    lives = 999;
    damage = 0;
    velocity = 0;
    position = pos;
    this->direction = direction;

    initial = false;
    condition = false;
    condition2 = false;
    condition3 = false;

    frameTimer = 0;
    frameDuration = 0.6f;
    deadTimer = 0;
    padding = 1;
    frames = 2;
    frameH = 33;
    frameW = 31;
    currentFrame = 0;

    alive = true;
    isAttacking = false;
    remove = false;
    damaged = false;

    if(direction == 1){
        HitBox = {position.x- 40, position.y, 50, 33};
    } else {
        HitBox = {position.x + 33 + 30, position.y, 50, 33};
    }
    attackingSprite = LoadTexture("sprites/characters/PaddySheet.png");

}

void Paddy::Update(float deltatime){
    if(player->dead) return;

    //this is for level 1, so that the cake only appears when the dialogue is done
    if(condition3 && !textBox->active){
        condition2 = true;
    }

    if(player->HandlePickingUp(HitBox, true)){
        switch (level){
            case 1:
                if(!initial){
                    textBox->EnqueuDialogue({
                        {"Hola, Teddy! Espero que te estés portando bien.", 
                        "¿Tienes hambre? ¿Qué tal si te preparo una deliciosa tarta \nde queso?",
                        "Aunque... no tengo aquí los ingredientes, necesito que me los traigas."
                    }, 5, "paddy"});
                    textBox->EnqueuDialogue({{"¿¿Por qué tengo que buscarlos yo??"}, 5, "teddy"});
                    textBox->EnqueuDialogue({{"Porque los has dejado tú tirados por ahí."}, 5, "paddy"});
                    textBox->EnqueuDialogue({{"Ah.", "No sé de qué me hablas pero te traeré tus ingredientes."}, 5, "teddy"});
                    textBox->EnqueuDialogue({{"¿Estás seguro que sabes qué ingredientes son los correctos?"}, 5, "paddy"});
                    textBox->EnqueuDialogue({{"¡Claro que sí! Ahora mismo vuelvo"}, 5, "teddy"});
                    initial = true;
                }
                else if(!condition){
                    textBox->EnqueuDialogue({{"¿Aún no me has traído los ingredientes?", "Si necesitas ayuda puedo ir contigo."}, 5, "paddy"});
                    textBox->EnqueuDialogue({{"¡No, no! El Teddy puede solo."}, 5, "teddy"});
                }
                else if(!condition2){

                    textBox->EnqueuDialogue({{"¡Muchas gracias, Teddy!", "Aunque... te ha faltado la mermelada."}, 5, "paddy"});
                    textBox->EnqueuDialogue({{"He traído algo mejor: ¡Gasolina!"}, 5, "teddy"});
                    textBox->EnqueuDialogue({{"No."}, 3, "paddy"});
                    textBox->EnqueuDialogue({{"Vale :)"}, 3, "teddy"});
                    textBox->EnqueuDialogue({{"En fin, ahora mismo te hago la tarta de queso.", "*Fiuuum*", "Ya está, Teddy."}, 3, "paddy"});
                    condition3 = true;
                }
                else{
                    textBox->EnqueuDialogue({{"Que aproveche, Teddy"}, 5, "paddy"});
                }

                break;

            default:
                textBox->EnqueuDialogue({{"No tengo nada que decir"}, 3, "paddy"});
        }
    }
}

void Paddy::Draw(float deltatime){
    Rectangle source = {(float)currentFrame*(frameW + padding), 0, (float)frameW*direction, (float)frameH};
    DrawTextureRec(attackingSprite, source, position, WHITE);
    frameTimer += deltatime;
    if(frameTimer >= frameDuration){
        frameTimer = 0;
        currentFrame++;
        if(currentFrame >= frames) currentFrame = 0;
    }
}

void Paddy::FadeBlack(float deltatime){

}

Wall::Wall(float level, Vector2 pos, int height, int width, Player* player, TextBox* textBox){

    this->player = player;
    this->textBox = textBox;

    lives = 3;
    maxLives = 3;
    position = pos;
    experience = 5;
    isAttacking = false;

    deadTimer = 0;

    damaged = false;

    alive = true;
    remove = false;

    HitBox = {position.x, position.y, (float)width, (float)height};
    if(level == 1){
        sheet = LoadTexture("sprites/maps/wallLevel1.png");
    }

    normal = {0, 0, (float)width, (float)height};
    broken1 = {(float)width+1, 0, (float)width, (float)height};
    broken2 = {(float)width*2+2, 0, (float)width, (float)height};
}

void Wall::Update(float deltatime){
    if(!alive) return;

    if(CheckCollisionRecs(player->HitBox, HitBox)){
        if(player->pos.x - position.x < 0){
            player->pos.x = position.x - player->width;
        } else player->pos.x = position.x + 32;
    }

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
            if(lives <= 0){
                player->experience += experience;
                alive = false;
                textBox->EnqueuDialogue({{"... Espero que a nadie le importe que haya roto eso jiji"}, 3, "teddy"});
                return;
            } 
        }
    }

    HitBox = {position.x, position.y, HitBox.width, HitBox.height};
}

void Wall::Draw(float deltatime){
    if(!alive){
        deadTimer += deltatime;
        if(deadTimer <= 2){
            std::string exp = "+" + std::to_string(experience) + " exp.";
            DrawText(exp.c_str(), player->pos.x, player->pos.y -15, 10, GREEN);
        }else{
            remove = true;
        }
        return;
    }
    
    switch (lives){
        case 3:
            DrawTextureRec(sheet, normal, position, WHITE);
            break;
        case 2: 
            DrawTextureRec(sheet, broken1, position, WHITE);
            break;
        case 1:
            DrawTextureRec(sheet, broken2, position, WHITE);
            break;
    }
}