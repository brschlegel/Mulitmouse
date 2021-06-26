#pragma once
#include "Level.h"
#include "Delegate.h"
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

