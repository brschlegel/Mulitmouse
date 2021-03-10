#include "LevelManager.h"


LevelManager::LevelManager()
{
	currentLevel = new DebugLevel();
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
	}
	currentLevel->init();
}
