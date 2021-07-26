#pragma once
#include "Level.h"

class MazeLevel :
    public Level
{
public:
    MazeLevel();
    Goal* left;
    Goal* right;
    void update();
    void init();
    vector<MouseCage*> cages;
};

