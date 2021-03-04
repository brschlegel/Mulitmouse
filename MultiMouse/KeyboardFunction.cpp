#include "KeyboardFunctions.h"

void DebugLevelKeyboard(Scene* scene)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		scene->world.AddBox(0, 4, 1, Color::getRed(), .5f, .5f);
	}
}

void DoNothing(Scene* scene)
{
	cout << "doNtohig";
}