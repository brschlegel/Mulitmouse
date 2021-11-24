#include "Box.h"

Box::Box(float x, float y, float mass, Color color, float height, float width,float friction,float density, float angle, std::string name) : PolygonPhysicsObject(x,y,mass,color,3,angle, name)
{
	setShapeAsBox(width, height);

	fixtureDef.shape = &shape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	this->height = height;
	this->width = width;
}

void Box::onCollision(PolygonObject* other)
{
	Mouse* m = dynamic_cast<Mouse*>(other);
	if (m != nullptr && selectable)
	{
		if (m->leftButtonPressed && m->physicsSelect == NULL)
		{
			body->SetType(b2_kinematicBody);
			body->SetLinearVelocity(b2Vec2_zero);
			selected = m;
			m->physicsSelect = this;
			onSelectDel.ExecuteIfBound(m);
		}
	}
}

void Box::updateObj()
{
	PolygonObject::updateObj();
}
