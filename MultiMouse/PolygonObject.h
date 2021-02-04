#pragma once
#include "GameObject.h"
#include <vector>
#include <GL/freeglut.h>
#include "Color.h"
class PolygonObject :
    public GameObject
{
public:
    std::vector<b2Vec2> vertices;
    PolygonObject(float x, float y, Color color, float angle);
    b2PolygonShape shape;
    virtual void draw();
    void setVertices(std::vector<b2Vec2> verts);
    void addVertex(b2Vec2 vert);
    void setShape();
    float angle;
    Color color = Color(1.0f,1.0f,1.0f);
    virtual void setShapeAsBox(float width, float height);
};


