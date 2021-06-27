#include "Level.h"

Level::Level()
{
	standardGravity = b2Vec2(0, -9.8f);
}

void Level::draw(sf::RenderWindow* window)
{
	currentScene->draw(window);
}

void Level::update()
{
	
	currentScene->update();
	
	if (scenes.find("instructions") != scenes.end() && currentScene == scenes["instructions"] && scenes["instructions"]->readyUpButton->checkFull())
	{
		MouseManager::getInstance()->unfreezeAllMice();
		currentScene = scenes["main"];
		scenes["main"]->init();
	
	}
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


