#include "Box.h"

Box::Box(float x, float y, float mass, Color color, float height, float width,float friction,float density, float angle ) : PolygonPhysicsObject(x,y,mass,color,angle)
{
	//addVertex(b2Vec2(-width / 2, -height / 2));
	//addVertex(b2Vec2(width / 2, -height / 2));
	//addVertex(b2Vec2(width / 2, height / 2));
	//addVertex(b2Vec2(-width / 2, height / 2));
	//setShape();
	setShapeAsBox(width, height);

	fixtureDef.shape = &shape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
}
