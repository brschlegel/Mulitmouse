#pragma once
#include "PolygonObject.h"

struct ControlPoint :
    public PolygonObject
{
    ControlPoint(b2Vec2 position, Color color);
};

