#include "LevelSelect.h"

LevelSelect::LevelSelect()
{
	Scene* main = new Scene(standardGravity, "main");
	LevelButton* dodgeball = main->shapes->buildLevelButton(-3, 4, 1.5f, .5f, Color::getBlue(), LevelName::Dodgeball);
	activationConditions[dodgeball] = 2;
	main->ui.buildLabelInTrigger("Dodgeball", dodgeball);

	/*LevelButton* debug = main->shapes->buildLevelButton(-6, 4, 1.5f, .5f, Color::getRed(), LevelName::DebugLevel);
	activationConditions[debug] = 1;
	main->ui.buildLabelInTrigger("Playbox", debug);*/

	LevelButton* juggling = main->shapes->buildLevelButton(0, 4, 1.5f, .5f, Color::getGreen(), LevelName::Juggling);
	activationConditions[juggling] = 2;
	main->ui.buildLabelInTrigger("Juggling", juggling);

	LevelButton* pong = main->shapes->buildLevelButton(3, 4, 1.5f, .5f, Color::getBlue(), LevelName::Pong);
	activationConditions[pong] = 2;
	main->ui.buildLabelInTrigger("Pong", pong);
	
	LevelButton* musical = main->shapes->buildLevelButton(6.0f, 4, 1.5f, .5f, Color::getBlue(), LevelName::Musical);
	activationConditions[musical] = 0;
	Label* musicalLabel = main->ui.buildLabelInTrigger("Non-Musical Chairs", musical, 14);

	LevelButton* maze = main->shapes->buildLevelButton(-6, 3, 1.5f, .5f, Color::getBlue(), LevelName::Maze);
	activationConditions[maze] = 4;
	main->ui.buildLabelInTrigger("Maze", maze);

	LevelButton* circus = main->shapes->buildLevelButton(-3, 3, 1.5f, .5f, Color::getBlue(), LevelName::Circus);
	activationConditions[circus] = 0;
	main->ui.buildLabelInTrigger("Circus", circus);


	LevelButton* curveMatch = main->shapes->buildLevelButton(0, 3, 1.5f, .5f, Color::getGreen(), LevelName::CurveMatch);
	activationConditions[curveMatch] = 0;
	main->ui.buildLabelInTrigger("Curve Match", curveMatch);

	

	LevelButton* WackAMole = main->shapes->buildLevelButton(3, 3, 1.5f, .5f, Color::getBlue(), LevelName::WackAMole);
	activationConditions[WackAMole] = 0;
	main->ui.buildLabelInTrigger("WackAMole", WackAMole);

	LevelButton* ClickRace = main->shapes->buildLevelButton(6, 3, 1.5f, 0.5f, Color::getBlue(), LevelName::ClickRace);
	activationConditions[ClickRace] = 2;
	main->ui.buildLabelInTrigger("ClickRace", ClickRace);

	//LevelButton* BrickBreaker = main->shapes->buildLevelButton(-3, 2, 1.5f, .5f, Color::getBlue(), LevelName::BrickBreaker);
	//activationConditions[BrickBreaker] = 0;
	//main->ui.buildLabelInTrigger("BrickBreaker", BrickBreaker);

	LevelButton* BasketBall = main->shapes->buildLevelButton(-6, 4, 1.5f, .5f, Color::getBlue(), LevelName::BasketBall);
	activationConditions[BasketBall] = 0;
	main->ui.buildLabelInTrigger("BasketBall", BasketBall);


	LevelButton* LeaderBoard = main->shapes->buildLevelButton(0, 0, 1.5f, .5f, Color(255, 189, 9), LevelName::LeaderBoard);
	activationConditions[LeaderBoard] = 1;
	main->ui.buildLabelInTrigger("Leaderboard", LeaderBoard);

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
			else
			{
				itr->first->active = true;
			}
		}
	}
}
