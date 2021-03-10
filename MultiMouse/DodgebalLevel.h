#pragma once
#include "Level.h"
class DodgeballLevel :
    public Level
{
public:
    DodgeballLevel(MouseManager* mouseManager);
    void update();
    void init();
    Goal* runner;
    MouseCage* leftCage;
    MouseCage* rightCage;
};

