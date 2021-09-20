#include "CubicBezier.h"

CubicBezier::CubicBezier(Color color, int LOD, int mask, std::string name) : Line(color, LOD, mask, name)
{
}

void CubicBezier::addControlPoint(PolygonObject* obj)
{
	controlPoints.push_back(obj);
}

void CubicBezier::update()
{
	placePoints();
}

void CubicBezier::placePoints()
{
	b2Vec2 p1 = b2Vec2(controlPoints[0]->x, controlPoints[0]->y);
	b2Vec2 p2 = b2Vec2(controlPoints[1]->x, controlPoints[1]->y);
	b2Vec2 p3 = b2Vec2(controlPoints[2]->x, controlPoints[2]->y);
	b2Vec2 p4 = b2Vec2(controlPoints[3]->x, controlPoints[3]->y);
	float tStep = 1.0f / LOD;
	float t = 0;
	for (int i = 0; i < LOD;i++ )
	{
		t += tStep;
		b2Vec2 a = std::pow(1 - t, 3) * p1;
		b2Vec2 b = std::pow(1 - t, 2) * 3 * t *p2;
		b2Vec2 c = (1-t) * std::pow(t, 2) * 3 * p3;
		b2Vec2 d = std::pow(t, 3) * p4;
		points[i].position = a + b + c + d;
	}
}
