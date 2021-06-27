#include "PolygonObject.h"
#include <iostream>
PolygonObject::PolygonObject(float x, float y, Color color ,unsigned int mask,Layer layer,float angle, std::string name) : GameObject(x,y, name)
{	
	this->angle = angle;
	this->color = color;
	this->mask = mask;
	this->layer = layer;
}


void PolygonObject::draw()
{
	glPushMatrix();
	glColor4f(color.r, color.g, color.b, color.a);
	glTranslatef(x, y, 0);
	glRotatef(angle * 180.0f/b2_pi, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < vertices.size(); i++)
	{
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
	glPopMatrix();
}

void PolygonObject::setVertices(std::vector<b2Vec2> verts)
{
	vertices = verts;
}

void PolygonObject::addVertex(b2Vec2 vert)
{
	vertices.push_back(vert);
}

void PolygonObject::setShape()
{
	b2Vec2* arr = &vertices[0];
	shape.Set(arr, vertices.size());
}

void PolygonObject::setShapeAsBox(float width, float height)
{
	addVertex(b2Vec2(- width / 2,  - height / 2));
	addVertex(b2Vec2( width / 2,  - height / 2));
	addVertex(b2Vec2( width / 2,  height / 2));
	addVertex(b2Vec2( -width / 2,  height / 2));
	setShape();
}

void PolygonObject::onCollision(PolygonObject* other)
{
}

