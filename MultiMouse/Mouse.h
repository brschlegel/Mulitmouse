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
	bool active;
	bool frozen;
	bool drawn;
	Color teamColor;
	float bounds[4];
	void SetBounds(float top, float bottom, float right, float left);
	void ResetBounds();
private:
};


