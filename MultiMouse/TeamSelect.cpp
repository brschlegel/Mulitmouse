#include "TeamSelect.h"

TeamSelect::TeamSelect(int numButtons, int perTeam, LevelName chainedLevel)
{
	this->chainedLevel = chainedLevel;
	float increment = 8.0f / numButtons;
	Scene* main = new Scene(standardGravity, "main");
	main->ui.buildLabel("Choose your teams! Don't be left out!", 0, 3, 30);
	scenes["main"] = main;
	for (int i = 0; i < numButtons; i++)
	{
		buttons.push_back(main->shapes->buildMouseAssignmentButton((increment * i) + (increment / 2) - 4, 0, increment / 2, 4, Color::getListOfColors()[i], perTeam));
	}

	currentScene = main;
}

void TeamSelect::update()
{
	checkLevelUpdate();
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

	MouseManager::getInstance()->resetMice(false);
	for (int i = 0; i < buttons.size(); i++)
	{
		MouseManager::getInstance()->setTeam(buttons[i]->mice, Color::getListOfColors()[i]);
		for (int j = 0; j < buttons[i]->mice.size(); j++)
		{
			buttons[i]->mice[j]->active = true;
		}
	}


	EventStorage::getInstance()->levelEvents.push_back((int)chainedLevel);
	return (int)chainedLevel;


}
