#include "LevelButton.h"

LevelButton::LevelButton(float x, float y, float width, float height, Color color, LevelName level, std::string name) : Trigger(x, y, width, height, color,1, name)
{
	this->level = level;
	this->triggerId = 3;
	active = false;
}

void LevelButton::onClick()
{
	//LevelManager::getInstance()->changeLevel(level);
}

void LevelButton::onStay()
{
}

void LevelButton::draw()
{
	glPushMatrix();
	if (active)
		glColor4f(color.r, color.g, color.b, color.a);
	else
		glColor4f(.5, .5, .5, .8);
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

void LevelButton::onCollision(PolygonObject* other)
{
	Mouse* m = dynamic_cast<Mouse*>(other);
	if (m != nullptr)
	{
		if (active && m->leftButtonPressed)
		{
			EventStorage::getInstance()->levelEvents.push_back((int)level);
		}
	}
}
