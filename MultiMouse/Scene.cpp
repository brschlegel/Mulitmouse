#include "Scene.h"

Scene::Scene(MouseManager* mouseManager, b2Vec2 gravity, std::string name)
{
	world =  PhysicsWorld(gravity);
	collisions =  CollisionManager(&world, mouseManager);
	ui =  UIManager();
	this->name = name;
}

void Scene::draw(sf::RenderWindow* window)
{
	world.draw();
	collisions.draw();
	ui.draw(window);
}

void Scene::update()
{
	world.Update();
	collisions.update();
}

