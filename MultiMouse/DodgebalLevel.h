#pragma once
#include "Level.h"
class DodgeballLevel :
    public Level
{
public:
    DodgeballLevel();
    void update();
    void init();
    Goal* runner;
    MouseCage* leftCage;
    MouseCage* rightCage;
};

