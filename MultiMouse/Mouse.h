#pragma once
#include <GL/freeglut.h> //include glut for Windows
#include "GameObject.h"
class Mouse : public GameObject
{
public:
	Mouse();
	float sensitivityCoeff;
	bool leftButtonPressed, rightButtonPressed;
	void draw();
	void updateX(float num);
	void updateY(float num);
private:
	float prevX, prevY;
};

