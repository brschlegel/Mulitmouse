#include "DodgebalLevel.h"

DodgeballLevel::DodgeballLevel(MouseManager* mouseManager) : Level(mouseManager)
{
	Scene* main = new Scene(mouseManager, standardGravity, "main");
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
	leftCage->AddMouse(mouseManager->mice[0]);
	leftCage->init();
}
