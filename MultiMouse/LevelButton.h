#pragma once
#include "Trigger.h"
class LevelManager;
class LevelButton :
    public Trigger
{
public:
    LevelName level;
    LevelButton(float x, float y, float width, float height, Color color,LevelName level, std::string name = "unnamed");
    void onClick();
    void onStay();
    void draw();

};

