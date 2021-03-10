#include "LevelManager.h"


LevelManager::LevelManager(MouseManager* mouseManager)
{
	this->mouseManager = mouseManager;
	currentLevel = new DebugLevel(mouseManager);
}

void LevelManager::changeLevel(LevelName newScene)
{
	currentLevel->unload();
	switch (newScene)
	{
	case LevelName::Juggling:
		currentLevel = new JugglingLevel(mouseManager);
		break;
	case LevelName::DebugLevel:
		currentLevel = new DebugLevel(mouseManager);
		break;
	case LevelName::Pong:
		currentLevel = new PongLevel(mouseManager);
		break;
	case LevelName::Dodgeball:
		currentLevel = new DodgeballLevel(mouseManager);
		break;
	}
	currentLevel->init();
}
