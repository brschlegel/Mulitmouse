#include "Line.h"

Line::Line(Color color, int LOD, int mask, std::string name) : GameObject(name)
{
	this->color = color;
	this->LOD = LOD;
	this->end = LOD;
	this->mask = mask;
}

void Line::draw()
{
	glPushMatrix();
	glBegin(GL_LINE);
	glColor4f(color.r, color.g, color.b, color.a);
	for (int i = 0; i < end; i++)
	{
		glVertex2f(points[i].position.x, points[i].position.y);
	}
	glEnd();
	glPopMatrix();
}

void Line::onCollision(PolygonObject* obj, int index)
{
	end = index;
	for (int i = 0; i < points.size(); i++)
	{
		if (i < end)
		{
			points[i].active = true;
		}
		else
		{
			points[i].active = false;
		}
	}
}
