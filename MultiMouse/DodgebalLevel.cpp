#include "DodgebalLevel.h"

DodgeballLevel::DodgeballLevel()
{
	mouseNum = -2;

	Scene* instructions = new Scene(standardGravity, "instructions");
	instructions->buildInstructionScene("DodgeBall", "In Dodgeball there is a red team and a blue team. Both teams cannot leave their designated areas, and are trying to hit the middle keyboard player with the supplied boxes. The keyboard player moves with WASD.","Dodgeball");
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	leftCage = main->shapes->buildCage(-7, 0, 4, 9, Color::getGreen());
	rightCage = main->shapes->buildCage(7, 0, 4, 9, Color::getBlue());
	runner = main->shapes->buildGoal(0, 0, .25, .25, Color::getBlue(), "Runner");
	main->frameScene();
	main->keyboardFunc = DodgeBallRunner;
	FuncTimer* spawnBall = new FuncTimer(5, -4, 10);
	spawnBall->del.BindLambda([main]()
		{
			main->shapes->AddBox(-6, 3, 1, Color::getRed(), .5, .5);
			main->shapes->AddBox(6, 3, 1, Color::getBlue(), .5, .5);
		});
	spawnBall->callFunc();
	
	main->funcTimers.push_back(spawnBall);

	//main->initSignal.connect(boost::bind(&DodgeballLevel::init, this));
	main->initDel.BindLambda([this]()
		{
			leftCage->init();
			rightCage->init();
		});
	
	scenes["main"] = main;
	currentScene = scenes["instructions"];

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("haha u lost");
	scenes["gameOver"] = gameOver;
}

void DodgeballLevel::update()
{
	Level::update();
	if (runner->score > 0)
	{
		MouseManager::getInstance()->resetBounds();
		currentScene = scenes["gameOver"];
	}
}

void DodgeballLevel::init()
{
	for (int i = 0; i < MouseManager::getInstance()->teams[0].size(); i++)
	{
		rightCage->AddMouse(MouseManager::getInstance()->teams[0][i]);
	}
	
	for (int i = 0; i < MouseManager::getInstance()->teams[1].size(); i++)
	{
		leftCage->AddMouse(MouseManager::getInstance()->teams[1][i]);
	}
	
	
	
}
