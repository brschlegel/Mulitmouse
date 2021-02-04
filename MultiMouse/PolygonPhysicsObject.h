#pragma once
#include "PolygonObject.h"
class PolygonPhysicsObject :
    public PolygonObject
{
public:
    PolygonPhysicsObject(float x, float y, float mass, Color color,float angle = 0 );
    b2Body* body;
    float mass;
    b2BodyDef def;
    void draw();
    void setShapeAsBox(float width, float height);
;};

