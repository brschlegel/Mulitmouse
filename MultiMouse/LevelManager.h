#pragma once
#include "Level.h"
#include <map>
#include "MouseManager.h"
#include "FuncTimer.h"
#include "DebugLevel.h"
#include "JugglingLevel.h"
#include "PongLevel.h"
#include "DodgebalLevel.h"
#include "LevelSelect.h"
#include "PlayerSelect.h"

class LevelManager;
class LevelManager
{
public:
	Level* currentLevel;

	void changeLevel(LevelName newLevel);
	void checkChangeLevel();
	static LevelManager* instance;
	static LevelManager* getInstance();
private:
	LevelManager();
};

