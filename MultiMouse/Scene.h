#pragma once
#include "PhysicsWorld.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include <string>
#define SFML_STATIC
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "Level.h";

class FuncTimer;
class Scene
{
public:
	PhysicsWorld world;
	CollisionManager collisions;
	UIManager ui;
	Scene(MouseManager* mouseManager, b2Vec2 gravity, std::string name);
	void draw(sf::RenderWindow* window);
	void update();
	void (*keyboardFunc)(Scene* scene);
	std::string name;
	std::vector<FuncTimer*> funcTimers;
	FuncTimer* getTimerByName(std::string name);
	PolygonPhysicsObject* getBodyByName(std::string name);
	Label* getLabelByName(std::string name);
	Trigger* getTriggerByName(std::string name);
	std::vector<PolygonPhysicsObject*> getBodyByTag(Tag tag);
	virtual void init();
	float width, height;


};

