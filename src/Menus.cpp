#include "include/Menus.h"
#include <raylib.h>

Menus::Menus(int id, int prev){
    this->id = id;
    prevLevel = prev;

    if(id == 0){

    }
}

void Menus::Draw(){
    if(id == 1){
        int middle = GetScreenWidth()/2 - MeasureText("Teddy: The Game", 100)/2;
        DrawText("Teddy: The Game", middle, 100, 100, BLACK);
    }
}