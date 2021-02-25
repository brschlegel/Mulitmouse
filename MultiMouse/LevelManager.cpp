#include "LevelManager.h"


LevelManager::LevelManager(MouseManager* mouseManager)
{
	standardGravity = b2Vec2(0, -9.8f);
	Scene* debugLevel =  new Scene(mouseManager, standardGravity, "debooging");
	levels[LevelName::DebugLevel] = debugLevel;
}
