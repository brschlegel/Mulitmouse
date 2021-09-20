#pragma once
#include "Line.h"
class CubicBezier :
    public Line
{
public:
    CubicBezier(Color color, int LOD, int mask, std::string name = "unnamed");
    std::vector<PolygonObject*> controlPoints;
    void addControlPoint(PolygonObject* obj);
    void update() override;
    void placePoints() override;
    
};

