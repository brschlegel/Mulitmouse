#pragma once
#include "Box.h"
#include "Barrier.h"
#include <vector>
class PhysicsWorld
{
public:
	void Update();
	PhysicsWorld(b2Vec2 gravity);
	PhysicsWorld();
	Box* AddBox(float x, float y, float mass, Color color, float height, float width, float friction = .3, float density = 1, float angle = 0);
	Barrier* AddRectBarrier(float x, float y, float width, float height, float angle = 0);
	void draw();
	b2Vec2 gravity;
	b2World* world;
	std::vector<PolygonPhysicsObject*> bodies;
	void deleteObject(int index);
	void deleteObject(PolygonPhysicsObject* object);
};

