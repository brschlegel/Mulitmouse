#include "COMBox.h"

//Must set contact listener to get collisions
COMBox::COMBox(float x, float y, float width, float height, Color color, std::string name) : Box(x,y,0,color,height, width,.3,1, 0, name )
{
	clickIncrement = .15f;
	selectable = false;
}

void COMBox::updateObj()
{
	b2Vec2 desiredPos = b2Vec2_zero;
	for (int i = 0; i < mice.size(); i++)
	{
		Mouse* m = mice[i];
		//Set weights
		if (m->leftButtonPressed && !m->prevLeft)
		{
			weights[i] += clickIncrement;
		}
		desiredPos += weights[i]  * b2Vec2(m->x, m->y) ;
	}
	b2Vec2 vel = desiredPos - body->GetTransform().p;
	if (vel.LengthSquared() > 1)
	{
		vel.Normalize();
	}
	body->SetLinearVelocity(10.0f * vel);
	normalizeWeights();
}

void COMBox::setTeam(std::vector<Mouse*> team)
{
	mice = team;
	for (Mouse* m : team)
	{
		weights.push_back(1.0f/team.size());
	}
}

void COMBox::normalizeWeights()
{
	float sum = 0;
	for (int i = 0; i < weights.size(); i++)
	{
		sum += weights[i];
	}
	//once we have sum
	for (int i = 0; i < weights.size(); i++)
	{
		weights[i] /= sum;
	}
}

//not calling base here so I can add code in the gl call
void COMBox::draw()
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
	
	for (int i = 0; i < mice.size(); i++)
	{
		
		glLineWidth(weights[i] * 5);
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(mice[i]->x - x, mice[i]->y - y);
		glEnd();
	}

	

	glPopMatrix();
}
