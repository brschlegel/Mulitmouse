#pragma once
#include "Trigger.h"
#include "Goal.h"
#include <vector>
#include "Physics.h"
#include "MouseManager.h"
#include <memory>
#include <typeinfo>
#include <iostream>
class CollisionManager
{
public:
	PhysicsWorld* world;
	MouseManager* mouseManager;
	std::vector<Trigger*> triggers;
	CollisionManager(PhysicsWorld* world, MouseManager* mouseManager);
	Goal* buildGoal(float x, float y, Color color);
	Goal* buildGoal(float x, float y, float width, float height, Color color);
	void update();
	void draw();
	bool drawDebugFlag;

};

