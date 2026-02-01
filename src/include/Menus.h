#ifndef MENUS_H
#define MENUS_H

#include <raylib.h>
#include <iostream>
#include "Player.h"

class Menus{
public:

    int id;
    /*
        0: Pause
        1: Starting Game
        2: To level 2
        3: To level 3
        ...
        6: To level 6
    */
    int prevLevel;
    Texture2D background;
    Texture2D coin;
    Texture2D coconut;
    Texture2D calvi; // for calvis killed counter

    Texture2D jugar;
    Texture2D siguiente;
    Texture2D resumir;
    Texture2D salir;

    bool jugarFlag;
    bool siguienteFlag;
    bool resumirFlag;

    Menus(int id, int prev);
    void Draw(Player* player);
    void Update();
    bool DrawAndHandleBtn(Texture2D sheet, Vector2 position);

};

#endif