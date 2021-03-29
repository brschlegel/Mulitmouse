#include "PlayerSelect.h"

PlayerSelect::PlayerSelect(int numButtons, LevelName chainedLevel)
{
	this->chainedLevel = chainedLevel;
	Scene* main = new Scene(standardGravity, "main");
	main->ui.buildLabel("Click on the squares to reserve your spot in the next game!", 0, 3, 30);
	float increment = 8.0f / numButtons;
	for (int i = 0; i < numButtons; i++)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float x = random * increment + (increment * i) - 4;
		float y = random * 4 - 2;
		buttons.push_back(main->collisions.buildMouseAssignmentButton(x, y, .5f, .5f, Color::getBlue(), 1));
	}

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
