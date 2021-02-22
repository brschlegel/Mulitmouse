#include "LevelManager.h"

LevelManager::LevelManager(MouseManager* mouseManager)
{
	standardGravity = b2Vec2(0, -9.8f);
	Level* debugLevel =  new Level(mouseManager, standardGravity);
	levels[LevelName::DebugLevel] = debugLevel;
}
