#pragma once
#include "Level.h"
#include <map>

class LevelSelect :
    public Level
{
public:
    LevelSelect();
    void update();
    void checkActive();
    map<LevelButton*, int> activationConditions;
};

