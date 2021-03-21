#include "LevelButton.h"

LevelButton::LevelButton(float x, float y, float width, float height, Color color, LevelName level, std::string name) : Trigger(x, y, width, height, color, true, false, name)
{
	this->level = level;
	this->triggerId = 3;
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
	glColor4f(color.r, color.g, color.b, color.a);
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
