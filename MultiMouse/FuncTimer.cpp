#include "FuncTimer.h"

void FuncTimer::start()
{
	clock = new sf::Clock();
}

void FuncTimer::update()
{
	if (clock->getElapsedTime().asSeconds() > numSeconds)
	{
		func();
		if (doesRepeat)
			clock->restart();
	}
}

FuncTimer::FuncTimer(float numSeconds, bool doesRepeat, std::string name)
{
	this->numSeconds = numSeconds;
	this->doesRepeat = doesRepeat;
	this->name = name;
}

void FuncTimer::SetFuncPointer(void(*funcPointer)())
{
	func = funcPointer;
}
