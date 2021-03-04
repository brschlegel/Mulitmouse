#include "LevelManager.h"


LevelManager::LevelManager(MouseManager* mouseManager)
{
	levels[LevelName::Juggling] = new JugglingLevel(mouseManager);
	levels[LevelName::DebugLevel] = new DebugLevel(mouseManager);
	levels[LevelName::Pong] = new PongLevel(mouseManager);

	
	
}
