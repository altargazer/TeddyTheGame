#ifndef LEVELS_H
#define LEVELS_H

#include <raylib.h>
#include <vector>
#include "Player.h"

class Levels{
public:

    //attr
    int id;
    Player* player;
    Rectangle exitRec;

    //map
    Texture2D background;
    std::vector<std::vector<int>> colliders;

    //methods
    Levels(int id, Player* player, float exitX, float exitY);
    void Draw();
    void ManageCollisions();
    bool ReachedExit(Player* p);

};


#endif