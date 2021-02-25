#include "Mouse.h"
#include "PolygonObject.h"
#include <iostream>

Mouse::Mouse(Color color) : PolygonObject(0, 0,color,0)
{
	sensitivityCoeff = 100;
	leftButtonPressed = false;
	physicsSelect = NULL;
	rightButtonPressed = false;
	setShapeAsBox(.25f, .25f);
}



void Mouse::updateX(float num)
{
	x += (num/sensitivityCoeff);
}

void Mouse::updateY(float num)
{
	y -= num/sensitivityCoeff;
}

void Mouse::update()
{
	if (physicsSelect != NULL)
	{
		//physicsSelect->body->SetTransform(b2Vec2(x, y), 0);
		b2Vec2 selectPos = physicsSelect->body->GetPosition();
		b2Vec2 desiredVel = b2Vec2(x - selectPos.x, y - selectPos.y);
		desiredVel *= 40.0f;
		physicsSelect->body->SetLinearVelocity(desiredVel);
	}
}


void Mouse::releasePhysicsSelect()
{
	physicsSelect->body->SetType(b2_dynamicBody);
	physicsSelect->selected = nullptr;
	physicsSelect = NULL;
	
}
