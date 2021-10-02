#include "MouseAssignmentButton.h"

MouseAssignmentButton::MouseAssignmentButton(float x, float y, float width, float height, Color color, int occupancy) : Trigger(x,y,width,height, color, 1)
{
	this->occupancy = occupancy;
	triggerId = 4;

}

void MouseAssignmentButton::draw()
{
	glPushMatrix();
	if (mice.size() < occupancy)
		glColor4f(color.r, color.g, color.b, color.a);
	else
		glColor4f(color.r,color.g,color.b, .5f);
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

void MouseAssignmentButton::addMouse(Mouse* m)
{
	mice.push_back(m);
}

bool MouseAssignmentButton::checkFull()
{
	return !(mice.size() < occupancy);
}

void MouseAssignmentButton::onCollision(PolygonObject* other)
{
	Mouse* m = dynamic_cast<Mouse*>(other);
	if (m != nullptr)
	{
		if (m->leftButtonPressed && !m->frozen && m->active)
		{
			if (!checkFull())
			{
				m->frozen = true;
				m->drawn = true;
				mice.push_back(m);
				
			}
		}

		if (m->frozen && m->rightButtonPressed)
		{
			m->frozen = false;
			mice.erase(std::find(mice.begin(), mice.end(), m));
		}
	}
}
