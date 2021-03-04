#pragma once
#include "Level.h"
class JugglingLevel :
    public Level
{
public:
    JugglingLevel(MouseManager* mouseManager);
    void update();
private:
    Goal* bottomGoal;
 
};

