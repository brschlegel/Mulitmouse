#pragma once
#include "Scene.h"
#include <map>
#include "FuncTimer.h"
#include "DebugLevel.h"
#include "JugglingLevel.h"
#include "PongLevel.h"
#include "DodgebalLevel.h"
enum class LevelName{DebugLevel, Juggling, Pong, Dodgeball};
class LevelManager
{
public:
	Level* currentLevel;
	MouseManager* mouseManager;
	LevelManager(MouseManager* mouseManager);
	void changeLevel(LevelName newScene);
private:
	
};

