#pragma once
#include "Level.h"
class DebugLevel :
    public Level
{
public:
    DebugLevel(MouseManager* mouseManager);
    void DebugKeyboard();
    void draw(sf::RenderWindow* window);
    void update();
};

