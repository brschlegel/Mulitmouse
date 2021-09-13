#pragma once
#include "GameObject.h"
#include <vector>
#include "LinePoint.h"
#include "PolygonObject.h"
class Line :
    public GameObject
{
public:
    Line(Color color, int LOD, int mask, std::string name = "unnamed");
    std::vector<LinePoint> points;
    int LOD;
    int end;
    unsigned int mask;
    Color color;
    void draw() override;
    void update();
    virtual void onCollision(PolygonObject* obj, int index);
};

