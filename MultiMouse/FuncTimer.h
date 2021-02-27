#pragma once
#include <string>;
#define SFML_STATIC
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
class FuncTimer
{
public:
	void start();
	void update();
	FuncTimer(float numSeconds, bool doesRepeat, std::string name = "unnamed");
	void SetFuncPointer(void (*funcPointer)());
	std::string name;
private:
	void (*func)();
	bool doesRepeat;
	float numSeconds;
	bool started = false;
	sf::Clock* clock;
};

