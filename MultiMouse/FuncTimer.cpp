#include "FuncTimer.h"

void FuncTimer::start()
{
	clock = new sf::Clock();
}

void FuncTimer::update(Scene* scene)
{
	if (numRepetitions < numRepeat)
	{
		float numSecond = clock->getElapsedTime().asSeconds();
		float expression = ((m * (numRepetitions + 1)) + b);
		if (clock->getElapsedTime().asSeconds() > (m * (numRepetitions + 1) + b))
		{
			func(scene);
			numRepetitions = numRepetitions + 1;
		}
	}
}

FuncTimer::FuncTimer(float m, float b, int numRepeat, std::string name)
{
	this->m = m;
	this->b = b;
	this->numRepeat = numRepeat;
	this->name = name;
	
}

void FuncTimer::SetFuncPointer(void(*funcPointer)(Scene* scene))
{
	func = funcPointer;
}

void FuncTimer::callFunc(Scene* scene)
{
	func(scene);
}
