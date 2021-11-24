#include "MusicalChairs.h"

MusicalChairs::MusicalChairs()
{
	mouseNum = 0;
	Scene* instructions = new Scene(standardGravity, "instructions");
	instructions->buildInstructionScene("Non-Musical Chairs", "In Non-Musical Chairs your mouse is turned invisible, and you must find your way to the boxes. Click on the box to secure your place in the next round Every now and then your mouse will flicker on the screen, revealing its current position. The round ends when the time limit has been reached or all boxes are full. Try to be the last player standing! ", "NonMusicalChairs");
	currentScene = instructions;
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	scenes["main"] = main;
	roundTimer = main->ui.buildTimer(9, 0, 0, 50, "MainFont", Color(0,0,0,.3f));
	roundNum = 0;
	FuncTimer* invis = new FuncTimer(3, -2, 20, "invis");
	invis->del.BindLambda([]()
		{
			vector<Mouse*> activeMice = MouseManager::getInstance()->getActiveMice();
			for (int i = 0; i < activeMice.size(); i++)
			{
				activeMice[i]->drawn = false;
			}
		}
	);
	main->funcTimers.push_back(invis);

	FuncTimer* vis = new FuncTimer(3, 0, 20, "vis");
	vis->del.BindLambda([]()
		{
			vector<Mouse*> activeMice = MouseManager::getInstance()->getActiveMice();
			for (int i = 0; i < activeMice.size(); i++)
			{
				activeMice[i]->drawn = true;
			}
		});
	main->funcTimers.push_back(vis);
	//startRound();

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	scenes["gameOver"] = gameOver;
	gameOver->buildGameOverScene("We have a winner!");
}

bool MusicalChairs::checkForNewRound()
{

	//see if timers value is zero
	if (roundTimer->getNumSeconds() < 0)
		return true;
	

	//see if any buttons arent full
	for (int i = 0; i < chairs.size(); i++)
	{
		if (!chairs[i]->checkFull())
			return false;
	}
	
	return true;
}

void MusicalChairs::startRound()
{
	
	//Deactivate dead mice if not first round
	if (roundNum > 0)
	{
		MouseManager::getInstance()->resetMice(false);
		for (int i = 0; i < chairs.size(); i++)
		{
			for (int j = 0; j < chairs[i]->mice.size(); j++)
			{
				chairs[i]->mice[j]->active = true;
			}
			scenes["main"]->shapes->deleteObject(chairs[i]);
		}
		chairs.clear();
		scenes["main"]->shapes->clear();
	}
	
	

	//move the mice to random positions
	vector<Mouse*> mice = MouseManager::getInstance()->getActiveMice();
	for (int i = 0; i < mice.size(); i++)
	{
		float randX = (rand() % 1600 - 800)/100.0f;
		float randY = (rand() % 1000 - 500) / 100.0f;

		mice[i]->x = randX;
		mice[i]->y = randY;
	}
	//make new chairs

	
	int numChairs = MouseManager::getInstance()->getNumOfActiveMice() - 1;
	for (int i = 0; i < numChairs; i++)
	{
		float randX = (rand() % 1600 - 800) / 100.0f;
		

		float randY = (rand() % 1000 - 500) / 100.0f;
	
		chairs.push_back(scenes["main"]->shapes->buildMouseAssignmentButton(randX, randY, 1, 1, Color::getBlue(), 1));
	}
	//reset timer
	roundTimer->reset();
	roundNum++;
}

void MusicalChairs::update()
{
	Level::update();
	if (currentScene == scenes["main"])
	{
		if (checkForNewRound())
		{
			startRound();
		}
		if (MouseManager::getInstance()->getNumOfActiveMice() <= 1)
		{
			currentScene = scenes["gameOver"];
			scenes["gameOver"]->ui.labels.erase(scenes["gameOver"]->ui.labels.begin());
			if (MouseManager::getInstance()->getNumOfActiveMice() == 1)
			{
				scenes["gameOver"]->ui.buildLabel("Player #" + MouseManager::getInstance()->getActiveMice()[0]->text.getString() + " wins!", 0, 0, 30);
				ScoreManager::getInstance()->incrementScore(MouseManager::getInstance()->getActiveMice()[0]);
			}
			else
				scenes["gameOver"]->ui.buildLabel("No one wins!", 0, 0, 30);
			
			MouseManager::getInstance()->resetMice(true);
		}

	}
}
