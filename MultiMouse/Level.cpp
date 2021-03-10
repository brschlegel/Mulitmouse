#include "Level.h"

Level::Level(MouseManager* mouseManager)
{
	this->mouseManager = mouseManager;
	standardGravity = b2Vec2(0, -9.8f);
}

void Level::draw(sf::RenderWindow* window)
{
	currentScene->draw(window);
}

void Level::update()
{
	currentScene->update();
}

void Level::init()
{
}

void Level::unload()
{
	for (std::map<std::string, Scene*>::iterator itr = scenes.begin(); itr != scenes.end(); itr++)
	{
		itr->second->unload();
		delete itr->second;
	}
}
