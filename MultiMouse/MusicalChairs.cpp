#include "MusicalChairs.h"

MusicalChairs::MusicalChairs()
{
	mouseNum = 0;
	Scene* instructions = new Scene(standardGravity, "instructions");
	instructions->buildInstructionScene("Non-Musical Chairs", "In Non-Musical Chairs your mouse is turned invisible, and you must find your way to the boxes. Click on the box to secure your place in the next round Every now and then your mouse will flicker on the screen, revealing its current position. The round ends when the time limit has been reached or all boxes are full. Try to be the last player standing! ", "Musical");
	currentScene = instructions;
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	scenes["main"] = main;
	roundTimer = main->ui.buildTimer(40, 0, 0, 50, "MainFont", Color(0,0,0,.3f));
	roundNum = 0;
	FuncTimer* invis = new FuncTimer(5, -4, 20, "invis");
	invis->SetFuncPointer(turnMiceInvisible);	
	main->funcTimers.push_back(invis);

	FuncTimer* vis = new FuncTimer(5, 0, 20, "vis");
	vis->SetFuncPointer(turnMiceVisible);
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
	cout << "Round Start" << endl;
	return true;
}

void MusicalChairs::startRound()
{
	cout << "Round " << roundNum << endl;
	
	//Deactivate dead mice if not first round
	if (roundNum > 0)
	{
		MouseManager::getInstance()->setAllMiceActive(false);
		for (int i = 0; i < chairs.size(); i++)
		{
			for (int j = 0; j < chairs[i]->mice.size(); j++)
			{
				cout << "reset a mouse active" << endl;
				chairs[i]->mice[j]->active = true;
			}
			delete chairs[i];
		}
		chairs.clear();
		scenes["main"]->collisions.triggers.clear();
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
		randX /= 2;

		float randY = (rand() % 1000 - 500) / 100.0f;
		randY /= 2;
		chairs.push_back(scenes["main"]->collisions.buildMouseAssignmentButton(randX, randY, 1, 1, Color::getBlue(), 1));
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
			MouseManager::getInstance()->setAllMiceActive(true);
		}

	}
}
