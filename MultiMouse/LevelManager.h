#pragma once
#include "Level.h"
#include <map>
enum class LevelName{DebugLevel, Juggling};
class LevelManager
{
public:
	map<LevelName, Level*> levels;
	LevelManager(MouseManager* mouseManager);
private:
	b2Vec2 standardGravity;
};

