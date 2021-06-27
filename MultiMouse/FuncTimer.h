#pragma once
#include <string>;
#include "Scene.h"
#include "Delegate.h"
class Scene;
class FuncTimer
{
public:
	void start();
	void update(Scene* scene);
	FuncTimer(float m, float b, int numRepeat = 1, std::string name = "unnamed");
	Delegate<void> del;
	void callFunc();
	std::string name;
	sf::Clock* clock;
private:
	void (*func)(Scene* scene);
	int numRepeat, numRepetitions;

	bool started = false;
	
	float m, b;
};

