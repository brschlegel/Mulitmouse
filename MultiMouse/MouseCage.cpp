#include "MouseCage.h"

MouseCage::MouseCage(float x, float y, Color color, std::string name) : Trigger(x,y,color,true,false,name)
{
	triggerId = 2;
}

MouseCage::MouseCage(float x, float y, float width, float height, Color color, std::string name) : Trigger(x,y,width,height,color,true,false,name)
{
	triggerId = 2;
}

void MouseCage::draw()
{
	glPushMatrix();
	
	glColor4f(color.r, color.g, color.b, .5f);
	glTranslatef(x, y, 0);
	glRotatef(angle * 180.0f / b2_pi, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < vertices.size(); i++)
	{
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
	glPopMatrix();
}

void MouseCage::onStay()
{
}

void MouseCage::AddMouse(Mouse* mouse)
{
	mice.push_back(mouse);
	if (mice.size() == 1)
	{
		this->color = mouse->color;
	}
}

void MouseCage::init()
{
	for (Mouse* m : mice)
	{
		m->x = x;
		m->y = y;
	}
}
