#include "Level.h"

Level::Level(MouseManager* mouseManager, b2Vec2 gravity)
{
	world =  PhysicsWorld(gravity);
	collisions =  CollisionManager(&world, mouseManager);
	ui =  UIManager();
}

void Level::draw(sf::RenderWindow* window)
{
	world.draw();
	collisions.draw();
	ui.draw(window);
}

void Level::update()
{
	world.Update();
	collisions.update();
}

