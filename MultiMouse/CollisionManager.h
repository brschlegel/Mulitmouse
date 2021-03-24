#pragma once
#include "Trigger.h"
#include "PhysicsWorld.h"
#include "MouseManager.h"
#include "Goal.h"
#include "MouseCage.h"
#include "LevelButton.h"
#include "MouseAssignmentButton.h"


class LevelManager;
class CollisionManager
{
public:
	PhysicsWorld* world;
	MouseManager* mouseManager;
	std::vector<Trigger*> triggers;
	int switchLevelFlag;
	CollisionManager(PhysicsWorld* world);
	CollisionManager();
	Goal* buildGoal(float x, float y, Color color, std::string name = "unnamed");
	Goal* buildGoal(float x, float y, float width, float height, Color color, std::string name = "unnamed");
	MouseCage* buildCage(float x, float y, Color color, std::string name = "unnamed");
	MouseCage* buildCage(float x, float y, float width, float height, Color color, std::string name = "unnamed");
	LevelButton* buildLevelButton(float x, float y, float width, float height, Color color, LevelName level, std::string name = "unnamed");
	MouseAssignmentButton* buildMouseAssignmentButton(float x, float y, float width, float height, Color color, int occupancy, std::string name = "unnamed");
	void unload();

	void update();
	void draw();
	bool drawDebugFlag;
	Trigger* getTriggerByName(std::string name);


};

