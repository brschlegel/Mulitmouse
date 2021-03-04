#pragma once
#include "Scene.h"
#include <map>
#include "FuncTimer.h"
#include "DebugLevel.h"
#include "JugglingLevel.h"
#include "PongLevel.h"
enum class LevelName{DebugLevel, Juggling, Pong};
class LevelManager
{
public:
	map<LevelName, Level*> levels;
	LevelManager(MouseManager* mouseManager);
private:
	
};

