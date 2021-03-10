#pragma once
#include "Level.h"
class DebugLevel :
    public Level
{
public:
    DebugLevel();
    void draw(sf::RenderWindow* window);
    void update();
};

