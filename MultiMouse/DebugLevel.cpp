#include "DebugLevel.h"
#include "KeyboardFunctions.h"
DebugLevel::DebugLevel()
{
	mouseNum = 1;
	scenes["main"]= new  Scene(standardGravity, "Main");

    scenes["main"]->world.AddRectBarrier(0, -5, 20, 1);
	scenes["main"]->world.AddRectBarrier(1, 5, 20, 1);
	scenes["main"]->world.AddRectBarrier(-9, 0, 1, 10);
	scenes["main"]->world.AddRectBarrier(9, 0, 1, 10);
	scenes["main"]->world.AddRectBarrier(0, 0, 1, 1);
	scenes["main"]->world.AddBox(0, 4, 1, Color::getRed(), .5f, .5f);
	scenes["main"]->collisions.buildGoal(-2, 2, 1, 1, Color::getGreen());
	scenes["main"]->keyboardFunc = DebugLevelKeyboard;
	currentScene = scenes["main"];
}

void DebugLevel::draw(sf::RenderWindow* window)
{
	currentScene->draw(window);
}

void DebugLevel::update()
{
	currentScene->update();
}

