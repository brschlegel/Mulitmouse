#pragma once
#include <map>
#include "Scene.h"
#include "MouseManager.h"
#define SFML_STATIC
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "FuncTimer.h"
#include "ScoreManager.h"



#include <cmath>
class Scene;
class Level
{
public:
	std::map<std::string, Scene*> scenes;
	Scene* currentScene;

	Level();
	virtual void draw(sf::RenderWindow* window);
	virtual void update();
	virtual void init();
	virtual void unload();
	int mouseNum;
protected:
	b2Vec2 standardGravity;

		
};

