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
	active = true;
	frozen = false;
	teamColor = Color(0, 0, 0);
	drawn = true;
}



void Mouse::updateX(float num)
{
	if (frozen)
		return;
	prevX = x;
	x += (num/sensitivityCoeff);

}

void Mouse::updateY(float num)
{
	if (frozen)
		return;
	prevY = y;
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

void Mouse::draw()
{
	if (!drawn)
		return;

	glPushMatrix();
	if (active)
		glColor4f(color.r, color.g, color.b, color.a);
	else
		glColor4f(color.r, color.g, color.b, .5f);
	glTranslatef(x, y, 0);
	glRotatef(angle * 180.0f / b2_pi, 0, 0, 1);
	glBegin(GL_POLYGON);

	std::vector<b2Vec2> drawVerts;
	float multi = 1.25f;
	drawVerts.push_back(multi * b2Vec2(-.1f, .1f));
	drawVerts.push_back(multi * b2Vec2(-.09f, -.06f));
	//drawVerts.push_back(b2Vec2(-.07f, -.04f));
	//drawVerts.push_back(b2Vec2(0,0));
	//drawVerts.push_back(b2Vec2(.03f, -.03f));
	drawVerts.push_back(multi * b2Vec2(.06f, .03f));

	for (int i = 0; i < drawVerts.size(); i++)
	{
		glVertex2f(drawVerts[i].x, drawVerts[i].y);
	}
	glEnd();
	float xOffset = 0; 
	float yOffset = 0;
	if (active)
		glColor3f(teamColor.r, teamColor.b, teamColor.g);
	else
		glColor4f(teamColor.r, teamColor.b, teamColor.g, .5f);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < drawVerts.size(); i++)
	{
		glVertex2f(drawVerts[i].x, drawVerts[i].y);
	}
	glEnd();

	

	glPopMatrix();
}
