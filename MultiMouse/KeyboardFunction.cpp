#include "KeyboardFunctions.h"

void DebugLevelKeyboard(Scene* scene)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		scene->shapes->AddBox(0, 4, 1, Color::getRed(), .5f, .5f);
	}
}

void DoNothing(Scene* scene)
{

}

void DodgeBallRunner(Scene* scene)
{
	
	Trigger* runner = scene->getTriggerByName("Runner");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (runner->y <4.35)
		{
			runner->y += .1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if(runner->x > -8.35)
			runner->x -= .1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if(runner->x < 8.35)
			runner->x += .1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (runner->y > -4.35)
		{
			runner->y -= .1;
		}
	}
}

