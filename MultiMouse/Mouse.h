#pragma once
#include "PolygonObject.h"
#include "PolygonPhysicsObject.h"
#include <iostream>
class PolygonPhysicsObject;
class Mouse : public PolygonObject
{
public:
	Mouse(Color color);
	float sensitivityCoeff;
	bool leftButtonPressed, rightButtonPressed;
	void updateX(float num);
	void updateY(float num);
	void update();
	PolygonPhysicsObject* physicsSelect;
	void releasePhysicsSelect();
	void draw();
	float prevX, prevY;
private:
};

