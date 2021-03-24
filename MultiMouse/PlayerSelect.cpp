#include "PlayerSelect.h"

PlayerSelect::PlayerSelect(int numButtons, LevelName chainedLevel)
{
	this->chainedLevel = chainedLevel;
	Scene* main = new Scene(standardGravity, "main");
	buttons.push_back(main->collisions.buildMouseAssignmentButton(1, 1, .5f, .5f, Color::getGreen(), 1));

	scenes["main"] = main;
	currentScene = scenes["main"];
}

void PlayerSelect::update()
{
	currentScene->update();
}

int PlayerSelect::checkLevelUpdate()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->mice.size() < buttons[i]->occupancy)
		{
			return -1;
		}
	}

	//if weve made it here prepare to switch levels
	MouseManager::getInstance()->setAllMiceActive(false);
	for (int i = 0; i < buttons.size(); i++)
	{
		for (int j = 0; j < buttons[i]->mice.size(); j++)
		{
			buttons[i]->mice[j]->active = true;
		}
	}
	return (int)chainedLevel;
}
