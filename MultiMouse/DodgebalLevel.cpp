#include "DodgebalLevel.h"

DodgeballLevel::DodgeballLevel()
{
	Scene* main = new Scene(standardGravity, "main");
	leftCage = main->collisions.buildCage(0, 0, 5, 5, Color::getGreen());
	main->frameScene();

	scenes["main"] = main;
	currentScene = scenes["main"];
}

void DodgeballLevel::update()
{
	currentScene->update();
}

void DodgeballLevel::init()
{
	leftCage->AddMouse(MouseManager::getInstance()->mice[0]);
	leftCage->init();
}
