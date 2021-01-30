#include "Mouse.h"
#include <iostream>

Mouse::Mouse()
{
	x = 0;
	y = 0;
	sensitivityCoeff = 100;
	leftButtonPressed = false;
	rightButtonPressed = false;
}

void Mouse::draw()
{
	glColor3f(0.0, 1.0, 1.0);
	// We draw a point at the origin of the drawing canvas; thus, its coordinates should be (0, 0).
	glPointSize(30.0f); // define the size of the point - the diameter of rasterized points. the default value is 1.
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void Mouse::updateX(float num)
{

	x += num/sensitivityCoeff;
	
}

void Mouse::updateY(float num)
{
	y -= num/sensitivityCoeff;
}
