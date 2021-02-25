#pragma once
#include "Scene.h"
#include <map>
enum class LevelName{DebugLevel, Juggling};
class LevelManager
{
public:
	map<LevelName, Scene*> levels;
	LevelManager(MouseManager* mouseManager);
private:
	b2Vec2 standardGravity;
};

