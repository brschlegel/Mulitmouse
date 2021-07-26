#pragma once
#include "GameObject.h"
#include <vector>
#include <GL/freeglut.h>
#include "Color.h"
#include "Delegate.h"
class PolygonObject;
enum class Layer{Physics = 4, Triggers = 2, Mice = 1};
class PolygonObject :
    public GameObject
{
public:
    std::vector<b2Vec2> vertices;
    PolygonObject(float x, float y,Color color, unsigned int mask, Layer layer,  float angle = 0, std::string name = "unnamed");
    b2PolygonShape shape;
    virtual void draw();
    void setVertices(std::vector<b2Vec2> verts);
    void addVertex(b2Vec2 vert);
    void setShape();
    float angle;
    Color color = Color(1.0f,1.0f,1.0f);
    virtual void setShapeAsBox(float width, float height);
    //0,0,0,0,0,Collides with bodies,Collides with triggers,Collides with mice
    unsigned int mask;
    virtual void onCollision(PolygonObject* other);
    Layer layer;
    virtual void updateObj();
    Delegate<void> updateDel;

    
};


