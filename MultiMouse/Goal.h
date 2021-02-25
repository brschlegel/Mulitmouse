#pragma once
#include "Trigger.h"
#include "Color.h"
#include "Physics.h"
class Goal :
    public Trigger
{
public:
    float score;
    Goal(float x, float y, Color color, std::string name = "unnamed");
    Goal(float x, float y, Color color, float width, float height, std::string name = "unnamed");
    void onEnter(PolygonObject* object);
    void onStay();
};

