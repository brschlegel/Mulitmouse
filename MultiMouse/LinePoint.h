#pragma once
#include <Box2D/Box2D.h>
#include "Color.h"
#include <GL/freeglut.h>
#include <iostream>

const float POINTSIDELENGTH = .05f;
struct LinePoint {
	
	bool active = true;
	b2Vec2 position;
	Color color;
	LinePoint(Color color)
	{
		this->color = color;
	}

};
