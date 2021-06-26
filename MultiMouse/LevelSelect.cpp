#include "LevelSelect.h"

LevelSelect::LevelSelect()
{
	Scene* main = new Scene(standardGravity, "main");
	LevelButton* dodgeball = main->shapes->buildLevelButton(-1.5f, 2, 1.5f, .5f, Color::getRed(), LevelName::Dodgeball);
	activationConditions[dodgeball] = -2;
	main->ui.buildLabelInTrigger("Dodgeball", dodgeball);

	LevelButton* debug = main->shapes->buildLevelButton(-3, 2, 1.5f, .5f, Color::getBlue(), LevelName::DebugLevel);
	activationConditions[debug] = 1;
	main->ui.buildLabelInTrigger("Playbox", debug);

	LevelButton* juggling = main->shapes->buildLevelButton(0, 2, 1.5f, .5f, Color::getGreen(), LevelName::Juggling);
	activationConditions[juggling] = 2;
	main->ui.buildLabelInTrigger("Juggling", juggling);

	LevelButton* pong = main->shapes->buildLevelButton(1.5f, 2, 1.5f, .5f, Color::getGreen(), LevelName::Pong);
	activationConditions[pong] = 2;
	main->ui.buildLabelInTrigger("Pong", pong);
	
	LevelButton* musical = main->shapes->buildLevelButton(3.0f, 2, 1.5f, .5f, Color::getBlue(), LevelName::Musical);
	activationConditions[musical] = 0;
	Label* musicalLabel = main->ui.buildLabelInTrigger("Non-Musical Chairs", musical, 14);
	


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
