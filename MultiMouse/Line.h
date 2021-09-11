#pragma once
#include "GameObject.h"
#include <vector>
#include "LinePoint.h"
class Line :
    public GameObject
{
public:
    Line(Color color, int LOD, std::string name = "unnamed");
    std::vector<LinePoint> points;
    int LOD;
    unsigned int mask;
    Color color;
    void draw() override;
    void update();
};

