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
