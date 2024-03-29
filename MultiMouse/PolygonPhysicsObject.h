#pragma once
#include "PolygonObject.h"
#include "Mouse.h"
class Mouse;
class PolygonPhysicsObject :
    public PolygonObject
{
public:
    PolygonPhysicsObject(float x, float y, float mass, Color color, unsigned int mask,float angle = 0, std::string name = "unnamed");
    b2Body* body;
    float mass;
    b2BodyDef def;
    void draw();
    Mouse* selected;
    bool selectable;
    void setShapeAsBox(float width, float height);
;};

