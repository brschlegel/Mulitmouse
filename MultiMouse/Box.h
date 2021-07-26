#pragma once
#include "PolygonPhysicsObject.h"

class Box :
    public PolygonPhysicsObject
{
public:
    
    b2FixtureDef fixtureDef;
    float width, height;
    Box(float x, float y, float mass,Color color, float height, float width ,float friction=.3, float density = 1, float angle = 0, std::string name = "unnamed");
    void onCollision(PolygonObject* other);
    virtual void updateObj();
};

