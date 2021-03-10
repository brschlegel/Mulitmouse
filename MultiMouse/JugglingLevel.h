#pragma once
#include "Level.h"
class JugglingLevel :
    public Level
{
public:
    JugglingLevel();
    void update();
private:
    Goal* bottomGoal;
 
};

