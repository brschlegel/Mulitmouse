#pragma once
#include "Level.h"
#include <map>
#include "FuncTimer.h"
#include "DebugLevel.h"
#include "JugglingLevel.h"
#include "PongLevel.h"
#include "DodgebalLevel.h"
#include "LevelSelect.h"
class LevelManager;
class LevelManager
{
public:
	Level* currentLevel;

	void changeLevel(LevelName newScene);
	void checkChangeLevel();
	static LevelManager* instance;
	static LevelManager* getInstance();
private:
	LevelManager();
};

