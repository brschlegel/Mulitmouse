#include "Line.h"

Line::Line(Color color, int LOD, int mask, std::string name) : GameObject(name)
{
	this->color = color;
	this->LOD = LOD;
	this->end = LOD;
	this->mask = mask;
	for (int i = 0; i < LOD; i++)
	{
		points.push_back(LinePoint(color));
	}
	renderPoints = false;
}

void Line::draw()
{
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	
	for (int i = 0; i < end; i++)
	{
		glColor4f(points[i].color.r, points[i].color.g, points[i].color.b, points[i].color.a);
		glVertex2f(points[i].position.x, points[i].position.y);
		
	}
	glEnd();

	if (renderPoints)
	{
		glPointSize(4);
		glBegin(GL_POINTS);
		
		for (int i = 0; i < end; i++)
		{
			glVertex3f(points[i].position.x, points[i].position.y, 0);
		}
		
		glEnd();
	}
	glPopMatrix();
	reset();
}

void Line::update()
{
	
}

void Line::reset()
{
	end = LOD;
	for (int i = 0; i < points.size(); i++)
	{
		points[i].active = true;
	}
}

void Line::onCollision(PolygonObject* obj, int index)
{
	if (index < end)
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
}
