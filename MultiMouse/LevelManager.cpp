#include "LevelManager.h"

LevelManager* LevelManager::instance;
LevelManager::LevelManager()
{
	currentLevel = new LevelSelect();
}

void LevelManager::changeLevel(LevelName newScene)
{
	currentLevel->unload();
	switch (newScene)
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
	case LevelName::LevelSelect:
		currentLevel = new LevelSelect();
		break;
	}
	currentLevel->init();
}

void LevelManager::checkChangeLevel()
{
	int level = currentLevel->checkLevelUpdate();
	if ( level != -1)
	{
		changeLevel((LevelName)level);
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
