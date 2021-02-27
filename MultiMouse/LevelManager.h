#pragma once
#include "Scene.h"
#include <map>
#include "FuncTimer.h"
#include "DebugLevel.h"
enum class LevelName{DebugLevel, Juggling};
class LevelManager
{
public:
	map<LevelName, Scene*> levels;
	LevelManager(MouseManager* mouseManager);
	DebugLevel* debugLevel;
private:
	
};

