#include "JugglingLevel.h"

JugglingLevel::JugglingLevel(MouseManager* mouseManager) : Level(mouseManager)
{
	Scene* main = new Scene(mouseManager, standardGravity, "main");
	//main->world.AddBox(0, 2, 1, Color::getRed(), .5, .5);
	bottomGoal = main->collisions.buildGoal(0, -2.5,100,1, Color::getBlue(), "Bottom");
	main->keyboardFunc = DoNothing;
	FuncTimer* spawnBoxTimer = new FuncTimer(5,-3, 10, "SpawnBox");
	spawnBoxTimer->SetFuncPointer(spawnKinematicBox);
	spawnBoxTimer->start();
	main->funcTimers.push_back(spawnBoxTimer);
	FuncTimer* dropBoxTimer = new FuncTimer(5,-3, 10, "DroppingBox");
	dropBoxTimer->SetFuncPointer(setBallDynamic);
	dropBoxTimer->start();
	main->funcTimers.push_back(dropBoxTimer);
	
	scenes["main"] = main;
	

	Scene* gameOver = new Scene(mouseManager, standardGravity, "gameOver");
	gameOver->ui.labels.push_back(new Label(sf::String("Haha u lost"), 800, 450,40, Color(0, 0, 0, 1), gameOver->ui.fonts["MainFont"], Color::getBlue()));
	gameOver->keyboardFunc = DoNothing;
	scenes["gameOver"] = gameOver;

	currentScene = scenes["main"];
}

void JugglingLevel::update()
{
	currentScene->update();
	if (currentScene->name == "main")
	{
		if (bottomGoal->score > 0)
		{
			currentScene = scenes["gameOver"];
		}
	}

	
}








