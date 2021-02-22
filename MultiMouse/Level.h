#pragma once
#include "PhysicsWorld.h"
#include "CollisionManager.h"
#include "UIManager.h"
#define SFML_STATIC
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
class Level
{
public:
	PhysicsWorld world;
	CollisionManager collisions;
	UIManager ui;
	Level(MouseManager* mouseManager, b2Vec2 gravity);
	void draw(sf::RenderWindow* window);
	void update();

};

