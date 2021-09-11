#pragma once
#include "Goal.h"
class MouseGoal :
    public Goal
{
public:
    vector<Mouse*> mice;
    MouseGoal(float x, float y, Color color, float width, float height, std::string name = "unnamed");
    void onCollision(PolygonObject* other);
};

