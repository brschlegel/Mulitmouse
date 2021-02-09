#pragma once
#include <GL/freeglut.h> //include glut for Windows
#include "PolygonObject.h"
#include "PolygonPhysicsObject.h"
#include <iostream>
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
private:
};

