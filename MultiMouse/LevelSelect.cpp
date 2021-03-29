#include "LevelSelect.h"

LevelSelect::LevelSelect()
{
	Scene* main = new Scene(standardGravity, "main");
	LevelButton* dodgeball = main->collisions.buildLevelButton(-1.5f, 2, 1.5f, .5f, Color::getRed(), LevelName::Dodgeball);
	activationConditions[dodgeball] = -2;
	main->ui.buildLabelInTrigger("Dodgeball", dodgeball);

	LevelButton* debug = main->collisions.buildLevelButton(-3, 2, 1.5f, .5f, Color::getBlue(), LevelName::DebugLevel);
	activationConditions[debug] = 1;
	main->ui.buildLabelInTrigger("Playbox", debug);

	LevelButton* juggling = main->collisions.buildLevelButton(0, 2, 1.5f, .5f, Color::getGreen(), LevelName::Juggling);
	activationConditions[juggling] = 2;
	main->ui.buildLabelInTrigger("Juggling", juggling);

	LevelButton* pong = main->collisions.buildLevelButton(1.5f, 2, 1.5f, .5f, Color::getGreen(), LevelName::Pong);
	activationConditions[pong] = 2;
	main->ui.buildLabelInTrigger("Pong", pong);
	


	main->frameScene();
	scenes["gameOver"] = main;
	currentScene = scenes["gameOver"];
}

void LevelSelect::update()
{
	currentScene->update();
	checkActive();
}

void LevelSelect::checkActive()
{
	for (auto itr = activationConditions.begin(); itr != activationConditions.end(); itr++)
	{
		if (MouseManager::getInstance()->mice.size() > 0)
		{
			if (itr->second > 0)
			{
				if (MouseManager::getInstance()->mice.size() >= itr->second)
				{
					itr->first->active = true;
				}
			}
			else if (itr->second < 0)
			{
				if (MouseManager::getInstance()->mice.size() % -itr->second == 0)
				{
					itr->first->active = true;
				}
			}
			else
			{
				itr->first->active = true;
			}
		}
	}
}
