#pragma once
#include <Box2D/Box2D.h>
#include "Color.h"
struct LinePoint {
	
	bool active = true;
	b2Vec2 position;
	Color color;
	LinePoint(Color color)
	{
		this->color = color;
	}
};
