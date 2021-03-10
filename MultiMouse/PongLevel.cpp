#include "PongLevel.h"

PongLevel::PongLevel()
{
	Scene* main = new Scene(standardGravity, "main");

	main->world.world->SetContactListener(&listener);
	for (int i = 0; i < 3; i++)
	{
		Box* b = main->world.AddBox(0, 2, 1, Color::getBlue(), .2, .2);
		b->selectable = false;
		b->body->SetGravityScale(0);
		b->body->SetType(b2_kinematicBody);
		b->addTag(Tag::Pong);
	}
	FuncTimer* moveBalls = new FuncTimer(2, 0);
	moveBalls->SetFuncPointer(MovePongBall);
	moveBalls->start();
	main->funcTimers.push_back(moveBalls);
	Box* paddle1 = main->world.AddBox(-2, 0, 1, Color::getBlue(), 2, .5);
	paddle1->addTag(Tag::Unscorable);
	Box* paddle2 = main->world.AddBox(2, 0, 1, Color::getRed(), 2, .5);
	paddle2->addTag(Tag::Unscorable);
	main->world.AddRectBarrier(0, -5, 20, 1);
	main->world.AddRectBarrier(1, 5, 20, 1);
	left = main->collisions.buildGoal(-5, 0,1,100, Color::getGreen(), "left");
	right = main->collisions.buildGoal(5, 0,1,100, Color::getGreen(), "right");

	main->keyboardFunc = DoNothing;
	scenes["main"] = main;
	currentScene = main;

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->ui.labels.push_back(new Label(sf::String("Haha u lost"), 800, 450, 40, Color(0, 0, 0, 1), gameOver->ui.fonts["MainFont"], Color::getBlue()));
	gameOver->keyboardFunc = DoNothing;
	scenes["gameOver"] = gameOver;
}

void PongLevel::update()
{
	currentScene->update();
	if (right->score > 0 || left->score > 0)
	{
		if (currentScene == scenes["main"])
		{
			sf::String loser;
			if (right->score > 0)
				loser = "Right";
			else
				loser = "left";
			scenes["gameOver"]->ui.labels.push_back(new Label(sf::String("Your " + loser + " side is weak!"), 760, 650, 40, Color(0, 0, 0, 1), scenes["gameOver"]->ui.fonts["MainFont"], Color::getBlue()));
		}
		currentScene = scenes["gameOver"];
	}
}

