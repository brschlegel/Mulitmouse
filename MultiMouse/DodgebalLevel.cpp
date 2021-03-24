#include "DodgebalLevel.h"

DodgeballLevel::DodgeballLevel()
{
	mouseNum = -2;
	Scene* main = new Scene(standardGravity, "main");
	leftCage = main->collisions.buildCage(-3.5, 0, 4, 9, Color::getGreen());
	rightCage = main->collisions.buildCage(3.5, 0, 4, 9, Color::getBlue());
	runner = main->collisions.buildGoal(0, 0, .25, .25, Color::getBlue(), "Runner");
	main->frameScene();
	main->keyboardFunc = DodgeBallRunner;
	FuncTimer* spawnBall = new FuncTimer(5, -4, 10);
	spawnBall->SetFuncPointer(SpawnDodgeBox);
	spawnBall->callFunc(main);
	spawnBall->start();
	main->funcTimers.push_back(spawnBall);

	
	scenes["main"] = main;
	currentScene = scenes["main"];

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->ui.labels.push_back(new Label(sf::String("Haha u lost"), 800, 450, 40, Color(0, 0, 0, 1), gameOver->ui.fonts["MainFont"], Color::getBlue()));
	gameOver->keyboardFunc = DoNothing;
	scenes["gameOver"] = gameOver;
}

void DodgeballLevel::update()
{
	currentScene->update();
	if (runner->score > 0)
	{
		currentScene = scenes["gameOver"];
	}
}

void DodgeballLevel::init()
{
	leftCage->AddMouse(MouseManager::getInstance()->mice[0]);
	rightCage->AddMouse(MouseManager::getInstance()->mice[1]);

	leftCage->init();
	rightCage->init();
}
