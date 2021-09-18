#include "ConnectingLine.h"

ConnectingLine::ConnectingLine(Color color, int LOD, int mask, std::string name) : Line(color, LOD, mask, name)
{
	for (int i = 0; i < LOD; i++)
	{
		points.push_back(LinePoint());
	}
}

void ConnectingLine::SetEnds(PolygonObject* source, PolygonObject* end)
{
	this->source = source;
	this->end = end;
}

void ConnectingLine::placePoints()
{
	b2Vec2 origin = b2Vec2(source->x, source->y);
	b2Vec2 direction = b2Vec2(end->x - source->x, end->y - source->y);
	//Normalizes direction and returns length
	float totalLength = direction.Normalize();
	float delta = totalLength / LOD;
	for (int i = 0; i < LOD; i++)
	{
		points[i].position = (delta * i * direction) + origin;
	}
}

void ConnectingLine::update()
{
	placePoints();
	
}
