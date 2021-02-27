#pragma once
#include <map>
#include "Scene.h"
#include "MouseManager.h"
#define SFML_STATIC
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
class Scene;
class Level
{
public:
	std::map<std::string, Scene*> scenes;
	Scene* currentScene;
	MouseManager* mouseManager;
	Level(MouseManager* mouseManager);
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void update();
protected:
	b2Vec2 standardGravity;

		
};

