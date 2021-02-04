#include "PolygonObject.h"
#include <iostream>
PolygonObject::PolygonObject(float x, float y, Color color ,float angle = 0) : GameObject(x,y)
{	
	this->angle = angle;
	this->color = color;
}

void PolygonObject::draw()
{
	glPushMatrix();
	glColor3f(color.r, color.g, color.b);
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
	addVertex(b2Vec2(x - width / 2, y - height / 2));
	addVertex(b2Vec2(x + width / 2, y - height / 2));
	addVertex(b2Vec2(x + width / 2, y + height / 2));
	addVertex(b2Vec2(x - width / 2, y + height / 2));
	setShape();
}

