#pragma once
#include "PolygonObject.h"
#include "Color.h"
#include <vector>

//IDs
//Goal : 1

class Trigger :
    public PolygonObject
{
public:
    Trigger(float x, float y, Color color, bool mouseTrigger, bool physicsTrigger, std::string name = "unnamed" );
    Trigger(float x, float y, float width, float height, Color color, bool mouseTrigger, bool physicsTrigger, std::string name = "unnamed");
    virtual void onEnter(PolygonObject* object);
    virtual void onStay() = 0;
    virtual void onLeave(PolygonObject* object);
    std::vector<PolygonObject*> objects;
    bool mouseTrigger;
    bool physicsTrigger;
    void drawDebug();
    int triggerId;

};

