#pragma once
#include "PolygonObject.h"
#include "PolygonPhysicsObject.h"
#define SFML_STATIC
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include <string>
#include "UIData.h"

class PolygonPhysicsObject;
class Mouse : public PolygonObject
{
public:
	sf::Text text;
	Mouse(Color color, int num);
	float sensitivityCoeff;
	bool leftButtonPressed, rightButtonPressed, prevLeft, prevRight;
	void updateX(float num);
	void updateY(float num);
	void update();
	PolygonPhysicsObject* physicsSelect;
	void releasePhysicsSelect();
	void draw(sf::RenderWindow* window);
	void drawGL();
	float prevX, prevY;
	bool active;
	bool frozen;
	bool drawn;
	bool isLeader;
	float score;
	float bounds[4];
	void SetBounds(float top, float bottom, float right, float left);
	void ResetBounds();
	bool operator > (const Mouse* other);
	
private:
};


