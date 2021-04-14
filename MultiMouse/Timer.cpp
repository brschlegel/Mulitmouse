#include "Timer.h"
#include <iostream>

Timer::Timer(float maxTime, int x, int y, int size, Color textColor, sf::Font font, Color backgroundColor, std::string name) : Label("Timer", x,y, size,textColor,font,backgroundColor, name)
{
	this->maxTime = sf::seconds(maxTime);
	this->currentTime = this->maxTime;

	clock = new sf::Clock();
}

void Timer::draw(sf::RenderWindow* window)
{
	currentTime = maxTime -  clock->getElapsedTime();

	//text->setString(std::to_string(currentTime.asSeconds()));
	std::string sec = std::to_string(round(currentTime.asSeconds()));
	std::string display;
	for (int i = 0; i < sec.size(); i++)
	{
		if (sec[i] == '.')
		{
			break;
		}
		display.push_back(sec[i]);
	}
	text->setString(display);
	Label::draw(window);
}

float Timer::getNumSeconds()
{
	return currentTime.asSeconds();
}

void Timer::reset()
{
	clock = new sf::Clock;
}


