#pragma once
#include <string>;
#define SFML_STATIC
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Scene.h"
class Scene;
class FuncTimer
{
public:
	void start();
	void update(Scene* scene);
	FuncTimer(float m, float b, int numRepeat = 1, std::string name = "unnamed");
	void SetFuncPointer(void (*funcPointer)(Scene* scene));
	void callFunc(Scene* scene);
	std::string name;
	sf::Clock* clock;
private:
	void (*func)(Scene* scene);
	int numRepeat, numRepetitions;

	bool started = false;
	
	float m, b;
};

