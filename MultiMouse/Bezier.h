#pragma once
#include "Line.h"
#include "BenMath.h"
class Bezier :
    public Line
{
public:
    Bezier(Color color, int LOD, int mask, std::string name = "unnamed");
    std::vector<PolygonObject*> controlPoints;
    void addControlPoint(PolygonObject* obj);
    void update() override;
    void placePoints() override;
    
};

