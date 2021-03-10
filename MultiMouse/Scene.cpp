#include "Scene.h"

Scene::Scene(MouseManager* mouseManager, b2Vec2 gravity, std::string name)
{
	world =  PhysicsWorld(gravity);
	collisions =  CollisionManager(&world, mouseManager);
	ui =  UIManager();
	this->name = name;
	keyboardFunc = DoNothing;
}

void Scene::draw(sf::RenderWindow* window)
{
	world.draw();
	collisions.draw();
	ui.draw(window);
}

void Scene::update()
{
	Scene* scene = this;
	world.Update();
	collisions.update();
	for (FuncTimer* t : funcTimers)
	{
		t->update(scene);
	}
}

FuncTimer* Scene::getTimerByName(std::string name)
{
	for (FuncTimer* t : funcTimers)
	{
		if (t->name == name)
		{
			return t;
		}
	}
	return nullptr;
}

PolygonPhysicsObject* Scene::getBodyByName(std::string name)			
{

	return world.getBodyByName(name);
}

Label* Scene::getLabelByName(std::string name)
{
	return ui.getLabelByName(name);
}

Trigger* Scene::getTriggerByName(std::string name)
{
	return collisions.getTriggerByName(name);
}

std::vector<PolygonPhysicsObject*> Scene::getBodyByTag(Tag tag)
{
	return world.getBodyByTag(tag);
}

void Scene::init()
{
	for (FuncTimer* t : funcTimers)
	{
		t->clock->restart();
	}
}

void Scene::frameScene()
{
	world.AddRectBarrier(0, -5, 20, 1);
	world.AddRectBarrier(1, 5, 20, 1);
	world.AddRectBarrier(-9, 0, 1, 10);
	world.AddRectBarrier(9, 0, 1, 10);
}

void Scene::unload()
{
	world.unload();
	collisions.unload();
	ui.unload();
	for (int i = 0; i < funcTimers.size(); i++)
	{
		delete funcTimers[i];
	}
}


