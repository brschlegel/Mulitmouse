#pragma once
#include "GameObject.h"
#include <vector>
#include "LinePoint.h"
#include "PolygonObject.h"
#include <iostream>
#include "ControlPoint.h"
class Line :
    public GameObject
{
public:
    Line(Color color, int LOD, int mask, std::string name = "unnamed");
    std::vector<LinePoint> points;
    int LOD;
    int end;
    bool renderPoints;
    unsigned int mask;
    Color color;
    void draw() override;
    virtual void update();
    void reset();
    virtual void placePoints() = 0;
    virtual void onCollision(PolygonObject* obj, int index);
};

