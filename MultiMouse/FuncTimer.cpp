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
			callFunc();
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



void FuncTimer::callFunc()
{
	del.ExecuteIfBound();
}
