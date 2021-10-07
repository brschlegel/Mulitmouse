#include "Mouse.h"
#include "PolygonObject.h"
#include <iostream>
#include <string>

float maxBounds[4] = { 5,-5,9,-9 };
Mouse::Mouse(Color color, int num) : PolygonObject(0, 0,color,6, Layer::Mice,0)
{
	sensitivityCoeff = 100;
	leftButtonPressed = false;
	physicsSelect = NULL;
	rightButtonPressed = false;
	setShapeAsBox(.25f, .25f);
	active = true;
	frozen = false;

	drawn = true;
	text = sf::Text();
	text.setString(std::to_string(num));
	text.setCharacterSize(24);
	text.setFont(UIData::getInstance()->fonts["MainFont"]);

	text.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, 255));
	sf::FloatRect textRect = text.getLocalBounds();

	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	std::copy(std::begin(maxBounds), std::end(maxBounds), std::begin(bounds));
	
}


void Mouse::updateX(float num)
{
	if (frozen)
		return;
	prevX = x;
	x += (num/sensitivityCoeff);
	if (x > bounds[2])
	{
		x = bounds[2];
	}
	if (x < bounds[3])
	{
		x = bounds[3];
	}
}

void Mouse::updateY(float num)
{
	if (frozen)
		return;
	prevY = y;
	y -= num/sensitivityCoeff;
	if (y > bounds[0])
	{
		y = bounds[0];
	}
	if (y < bounds[1])
	{
		y = bounds[1];
	}
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
		physicsSelect = nullptr;
	
	
}

void Mouse::draw(sf::RenderWindow* window)
{
	if (!drawn)
		return;
	
	drawGL();
	
	window->pushGLStates();

	
		
	if (active)
		text.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, 255));
	else
		text.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, 255.0f/2));


	auto textPos = UIData::getInstance()->convertWorldToUICoords(x, y);
	text.setFont(UIData::getInstance()->fonts["MainFont"]);
	text.setPosition(textPos.x, textPos.y);
	
	window->draw(text);
	
	window->popGLStates();


	

	
}

void Mouse::drawGL()
{

	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(angle * 180.0f / b2_pi, 0, 0, 1);
	//back fill
	glBegin(GL_POLYGON);
	glColor4f(1, 1, 1, 1);
	for (int i = 0; i < vertices.size(); i++)
	{

		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	if(active)
		glColor4f(color.r, color.g, color.b, 1);
	else
		glColor4f(color.r, color.g, color.b, .5f);
	for (int i = 0; i < vertices.size(); i++)
	{

		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
	glPopMatrix();
}

void Mouse::SetBounds(float top, float bottom, float right, float left)
{
	bounds[0] = top;
	bounds[1] = bottom;
	bounds[2] = right;
	bounds[3] = left;
}

void Mouse::ResetBounds()
{
	std::copy(std::begin(maxBounds), std::end(maxBounds), std::begin(bounds));

}
