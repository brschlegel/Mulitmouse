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
	teamColor = Color(0, 0, 0);
	drawn = true;
	text = sf::Text();
	text.setString(std::to_string(num));
	text.setCharacterSize(16);
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
	physicsSelect = NULL;
	
}

void Mouse::draw(sf::RenderWindow* window)
{
	if (!drawn)
		return;

	glPushMatrix();
	if (active)
		glColor4f(color.r, color.g, color.b, color.a);
	else
		glColor4f(color.r, color.g, color.b, .5f);
	glColor4f(0, 0, 0, 1);
	glTranslatef(x, y, 0);
	glRotatef(angle * 180.0f / b2_pi, 0, 0, 1);

	std::vector<b2Vec2> drawVerts;
	float multi = 1.25f;
	drawVerts.push_back(multi * b2Vec2(-.1f, .1f));
	drawVerts.push_back(multi * b2Vec2(-.09f, -.06f));
	//drawVerts.push_back(b2Vec2(-.07f, -.04f));
	//drawVerts.push_back(b2Vec2(0,0));
	//drawVerts.push_back(b2Vec2(.03f, -.03f));
	drawVerts.push_back(multi * b2Vec2(.06f, .03f));
	auto textPos = UIData::getInstance()->convertWorldToUICoords(x, y);
	text.setFont(UIData::getInstance()->fonts["MainFont"]);
	text.setPosition(textPos.x, textPos.y);
	std::cout << textPos.x << "y: " << textPos.y << std::endl;
	window->draw(text);
	float xOffset = 0; 
	float yOffset = 0;
	if (active)
		glColor3f(teamColor.r, teamColor.b, teamColor.g);
	else
		glColor4f(teamColor.r, teamColor.b, teamColor.g, .5f);


	

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
