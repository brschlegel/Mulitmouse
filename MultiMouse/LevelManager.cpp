#include "LevelManager.h"

LevelManager* LevelManager::instance;
LevelManager::LevelManager()
{
	currentLevel = new LevelSelect();
}

void LevelManager::changeLevel(LevelName newLevel)
{
	currentLevel->unload();
	MouseManager::getInstance()->unfreezeAllMice();
	switch (newLevel)
	{
	case LevelName::Juggling:
		currentLevel = new JugglingLevel();
		break;
	case LevelName::DebugLevel:
		currentLevel = new DebugLevel();
		break;
	case LevelName::Pong:
		currentLevel = new PongLevel();
		break;
	case LevelName::Dodgeball:
		currentLevel = new DodgeballLevel();
		break;
	case LevelName::Musical:
		currentLevel = new MusicalChairs();
		break;
	case LevelName::LevelSelect:
		MouseManager::getInstance()->setAllMiceActive();
		MouseManager::getInstance()->clearTeams();
		currentLevel = new LevelSelect();
		break;
	}
	if (currentLevel->mouseNum > 0)
	{
		if (MouseManager::getInstance()->getNumOfActiveMice() > currentLevel->mouseNum)
		{
			currentLevel = new PlayerSelect(currentLevel->mouseNum, newLevel);
		}
	}
	else if (currentLevel->mouseNum < 0 && MouseManager::getInstance()->teams.size() == 0)
	{
		if (MouseManager::getInstance()->getNumOfActiveMice() >= -currentLevel->mouseNum)
		{
			currentLevel = new TeamSelect(-currentLevel->mouseNum, MouseManager::getInstance()->getNumOfActiveMice() / -currentLevel->mouseNum, newLevel);
		}
	}



	currentLevel->init();
}

void LevelManager::checkChangeLevel()
{
	if (EventStorage::getInstance()->levelEvents.size() > 0)
	{
		changeLevel((LevelName)EventStorage::getInstance()->levelEvents[0]);
		EventStorage::getInstance()->levelEvents.clear();
	}
}

LevelManager* LevelManager::getInstance()
{
	if (!instance)
	{
		instance = new LevelManager();
	}
	return instance;
}
