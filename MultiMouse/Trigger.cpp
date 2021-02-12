#include "Trigger.h"

Trigger::Trigger(float x, float y, Color color, bool mouseTrigger, bool physicsTrigger) : PolygonObject(x, y, color, 0)
{
	this->mouseTrigger = mouseTrigger;
	this->physicsTrigger = physicsTrigger;
}

Trigger::Trigger(float x, float y, float width, float height, Color color, bool mouseTrigger, bool physicsTrigger) :PolygonObject(x, y, color, 0)
{
	this->mouseTrigger = mouseTrigger;
	this->physicsTrigger = physicsTrigger;
	setShapeAsBox(width, height);
}

void Trigger::onEnter(PolygonObject* object)
{
	objects.push_back(object);
}

void Trigger::onLeave(PolygonObject* object)
{
	objects.erase(std::find(objects.begin(), objects.end(), object));
}

void Trigger::drawDebug()
{
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(x, y, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < vertices.size(); i++)
	{
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
	glPopMatrix();
}
