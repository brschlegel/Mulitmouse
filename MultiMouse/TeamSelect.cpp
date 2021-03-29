#include "TeamSelect.h"

TeamSelect::TeamSelect(int numButtons, int perTeam, LevelName chainedLevel)
{
	this->chainedLevel = chainedLevel;
	float increment = 8.0f / numButtons;
	Scene* main = new Scene(standardGravity, "main");
	scenes["main"] = main;
	for (int i = 0; i < numButtons; i++)
	{
		buttons.push_back(main->collisions.buildMouseAssignmentButton((increment * i) + (increment / 2) - 4, 0, increment / 2, 4, Color::getListOfColors()[i], perTeam));
	}
	cout << buttons.size();
	currentScene = main;
}

void TeamSelect::update()
{
	Level::update();
}

int TeamSelect::checkLevelUpdate()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->mice.size() < buttons[i]->occupancy)
		{
			return -1;
		}
	}

	MouseManager::getInstance()->setAllMiceActive(false);
	for (int i = 0; i < buttons.size(); i++)
	{
		MouseManager::getInstance()->setTeam(buttons[i]->mice, Color::getListOfColors()[i]);
		for (int j = 0; j < buttons[i]->mice.size(); j++)
		{
			buttons[i]->mice[j]->active = true;
		}
	}



	return (int)chainedLevel;


}
