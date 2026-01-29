#ifndef MENUS_H
#define MENUS_H

#include <raylib.h>
#include <iostream>

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

   Rectangle start; //for first screen
   Rectangle goToNext; //for inbetween levels
   Rectangle resume; //for pause

   Menus(int id, int prev);
   void Draw();

};

#endif