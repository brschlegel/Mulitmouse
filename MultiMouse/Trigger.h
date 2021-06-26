#pragma once
#include "PolygonObject.h"
#include "Color.h"
#include <vector>
#include "EventStorage.h"
#include "Mouse.h"

//IDs
//Goal : 1
//MouseCage: 2
//Level Button 3

class Trigger :
    public PolygonObject
{
public:
    Trigger(float x, float y, Color color, unsigned int mask, std::string name = "unnamed" );
    Trigger(float x, float y, float width, float height, Color color, unsigned int mask,std::string name = "unnamed");
    virtual void onEnter(PolygonObject* object);
    virtual void onLeave(PolygonObject* object);
    std::vector<PolygonObject*> objects;
    bool mouseTrigger;
    bool physicsTrigger;
    void drawDebug();
    int triggerId;

};

