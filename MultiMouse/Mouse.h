#pragma once
#include <GL/freeglut.h> //include glut for Windows
class Mouse
{
public:
	Mouse();
	float x, y;
	bool leftButtonPressed, rightButtonPressed;
	void draw();
	void updateX(float num);
	void updateY(float num);
};

