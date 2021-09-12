#pragma once
#include "Level.h"

class CircusLevel :
    public Level
{
public:
    CircusLevel();
    vector<MouseGoal*> goals;
    void update();
    b2Vec2 startingPosition;
    MouseGoal* finish;
};

