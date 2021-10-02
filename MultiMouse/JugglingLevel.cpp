#include "JugglingLevel.h"

JugglingLevel::JugglingLevel() 
{
	mouseNum = 2;
	Scene* instructions = new Scene(standardGravity, "instructions");
	instructions->buildInstructionScene("Juggling", "Boxes will continually be dropped from the center of the screen. You lose if they fall to the bottom of the screen. Good Luck", "Juggling");
	scenes["instructions"] = instructions;

	Scene* main = new Scene( standardGravity, "main");
	//main->world.AddBox(0, 2, 1, Color::getRed(), .5, .5);
	bottomGoal = main->shapes->buildGoal(0, -5,100,1, Color::getBlue(), "Bottom");
	main->keyboardFunc = DoNothing;
	FuncTimer* spawnBoxTimer = new FuncTimer(5,-3, 10, "SpawnBox");
	spawnBoxTimer->del.BindLambda([main, this]()
		{
			Box* b = main->shapes->AddBox(0, 2, 1, Color::getRed(), .5, .5);
			b->body->SetType(b2_kinematicBody);
			b->addTag(Tag::Ball);
			count++;
		});
	//spawnBoxTimer->start();
	main->funcTimers.push_back(spawnBoxTimer);
	FuncTimer* dropBoxTimer = new FuncTimer(5,-3, 10, "DroppingBox");
	dropBoxTimer->del.BindLambda([main]()
		{
			for (PolygonPhysicsObject* ball : main->getBodyByTag(Tag::Ball))
			{
				if (ball->body->GetType() != b2_dynamicBody)
				{
					ball->body->SetType(b2_dynamicBody);
				}
			}
		});

	main->shapes->AddRectBarrier(0, 7, 100, 1);
	main->shapes->AddRectBarrier(9, 0, 1, 10);
	main->shapes->AddRectBarrier(-9, 0, 1, 10);
	main->funcTimers.push_back(dropBoxTimer);
	scenes["main"] = main;

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("haha u lost");
	scenes["gameOver"] = gameOver;

	currentScene = scenes["instructions"];
}

void JugglingLevel::update()
{
	Level::update();
	if (currentScene->name == "main")
	{
		if (bottomGoal->score > 0)
		{
			currentScene = scenes["gameOver"];
			currentScene->getLabelByName("losing")->SetString("Congrats, you juggled " + to_string(count - 1) + " boxes!");
		}
	}

	
}








