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
#include "TeamSelect.h"
#include "MusicalChairs.h"
#include "MazeLevel.h"
#include "CircusLevel.h"
#include "CurveMatch.h"
#include "WackAMole.h"
#include "ClickRace.h"
#include "Leaderboard.h"


class LevelManager;
class LevelManager
{
public:
	Level* currentLevel;

	void changeLevel(LevelName newLevel);
	void checkChangeLevel();
	map<LevelName, int> reqs;
	static LevelManager* instance;
	static LevelManager* getInstance();
private:
	LevelManager();
};

