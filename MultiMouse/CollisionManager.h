#pragma once
#include "Trigger.h"
#include "Goal.h"
#include <vector>
#include "Physics.h"
#include "MouseManager.h"
#include "MouseCage.h"
#include <memory>
#include <typeinfo>
#include <iostream>
class CollisionManager
{
public:
	PhysicsWorld* world;
	MouseManager* mouseManager;
	std::vector<Trigger*> triggers;
	CollisionManager(PhysicsWorld* world);
	CollisionManager();
	Goal* buildGoal(float x, float y, Color color, std::string name = "unnamed");
	Goal* buildGoal(float x, float y, float width, float height, Color color, std::string name = "unnamed");
	MouseCage* buildCage(float x, float y, Color color, std::string name = "unnamed");
	MouseCage* buildCage(float x, float y, float width, float height, Color color, std::string name = "unnamed");
	void unload();

	void update();
	void draw();
	bool drawDebugFlag;
	Trigger* getTriggerByName(std::string name);


};

