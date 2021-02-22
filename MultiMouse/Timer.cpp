#include "Timer.h"

Timer::Timer(float maxTime, int x, int y, int size, Color textColor, sf::Font font, Color backgroundColor) : Label("Timer", x,y, size,textColor,font,backgroundColor)
{
	this->maxTime = sf::seconds(maxTime);

	clock = new sf::Clock();
}

void Timer::draw(sf::RenderWindow* window)
{
	currentTime = maxTime -  clock->getElapsedTime();

	//text->setString(std::to_string(currentTime.asSeconds()));
	text->setString(std::to_string(round(currentTime.asSeconds())).substr(0,2));
	Label::draw(window);
}
