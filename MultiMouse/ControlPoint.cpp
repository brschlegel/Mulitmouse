#include "ControlPoint.h"

float sideLength = .1f;
ControlPoint::ControlPoint(b2Vec2 position, Color color) : PolygonObject(position.x, position.y, color, 0,Layer::None)
{
	float a = sqrt(3) / 3 * sideLength;
	float b = a / 2;
	
	addVertex(b2Vec2((sideLength / 2), -b));
	addVertex(b2Vec2(-(sideLength / 2), -b));
	addVertex(b2Vec2(0,a));
	setShape();

}
