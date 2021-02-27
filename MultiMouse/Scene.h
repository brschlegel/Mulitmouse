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

};

