#pragma once
#include "Line.h"
class ConnectingLine :
    public Line
{
public:
    ConnectingLine(Color color, int LOD, int mask, std::string name = "unnamed");
    PolygonObject* source;
    PolygonObject* end;
    void SetEnds(PolygonObject* source, PolygonObject* end);
    void placePoints();
    void update();

};

