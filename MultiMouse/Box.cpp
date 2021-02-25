#include "Box.h"

Box::Box(float x, float y, float mass, Color color, float height, float width,float friction,float density, float angle, std::string name) : PolygonPhysicsObject(x,y,mass,color,angle, name)
{
	setShapeAsBox(width, height);

	fixtureDef.shape = &shape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
}
