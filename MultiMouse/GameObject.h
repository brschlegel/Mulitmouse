#pragma once
#include <Box2D/Box2D.h>
#include <GL/freeglut.h>
#include "Color.h"
class GameObject
{
public:
	float x, y;
	virtual void draw() = 0;
	GameObject(float x, float y);
	
};

