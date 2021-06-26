#pragma once
#include "PhysicsWorld.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "FuncTimer.h"
#include "KeyboardFunctions.h"
#include "FuncTimerFunctions.h"
#include <string>
#define SFML_STATIC
#define BOOST_USE_WINDOWS_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "ShapeManager.h"
#include "Delegate.h"
#include <boost/signals2.hpp>

class CollisionManager;
class FuncTimer;
class Scene
{
public:
	ShapeStorage* shapes;
	UIManager ui;
	Scene(b2Vec2 gravity, std::string name);
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
	void frameScene();
	void unload();
	MouseAssignmentButton* readyUpButton;
	void buildInstructionScene(std::string levelName, std::string instructionText, std::string imageName);
	void buildGameOverScene(std::string losingMessage);

	void startFuncTimers();
	boost::signals2::signal<void()> initSignal;
};
