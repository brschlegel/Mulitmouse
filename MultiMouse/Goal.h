#pragma once
#include "Trigger.h"
#include "Color.h"
#include "Physics.h"
class Goal :
    public Trigger
{
public:
    float score;
    Goal(float x, float y, Color color);
    Goal(float x, float y, Color color, float width, float height);
    void onEnter(PolygonObject* object);
    void onStay();
};

