#include "PolygonPhysicsObject.h"

PolygonPhysicsObject::PolygonPhysicsObject(float x, float y,  float mass, Color color,float angle) : PolygonObject(x,y,color, angle)
{
	
	selected = false;
	def.position.Set(x, y);
	def.angle = angle * b2_pi;
	this->mass = mass;
	if (mass <= 0)
	{
		def.type = b2_staticBody;
	}
	else
	{
		def.type = b2_dynamicBody;
	}

}

void PolygonPhysicsObject::draw()
{
	glPushMatrix();
	
	glColor3f(color.r, color.g, color.b);
	glTranslatef(body->GetPosition().x, body->GetPosition().y, 0);
	glRotatef(angle * 180.0f / b2_pi, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < vertices.size(); i++)
	{
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
	//adding a bit of padding due to polygon skinning in box 2d
	if (selected)
		glColor3f(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < vertices.size(); i++)
	{
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
	glPopMatrix();
}

void PolygonPhysicsObject::setShapeAsBox(float width, float height)
{
	addVertex(b2Vec2(-width / 2, -height / 2));
	addVertex(b2Vec2(width / 2, -height / 2));
	addVertex(b2Vec2(width / 2, height / 2));
	addVertex(b2Vec2(-width / 2, height / 2));
	setShape();
}
