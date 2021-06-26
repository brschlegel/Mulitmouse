#include "PongLevel.h"

PongLevel::PongLevel()
{
	mouseNum = 2;
	Scene* main = new Scene(standardGravity, "main");

	Scene* instructions = new Scene(standardGravity, "instructions");
	instructions->buildInstructionScene("Pong", "Ah the classic game Pong. Except you have to actively hold the paddles, and you can move them wherever you want. And there are multiple balls. And the physics are wackier. Whatever, just don't lose", "Pong");
	scenes["instructions"] = instructions;

	main->shapes->world->SetContactListener(&listener);
	for (int i = 0; i < 3; i++)
	{
		Box* b = main->shapes->AddBox(0, 2, 1, Color::getBlue(), .2, .2);
		b->selectable = false;
		b->body->SetGravityScale(0);
		b->body->SetType(b2_kinematicBody);
		b->addTag(Tag::Pong);
	}
	FuncTimer* moveBalls = new FuncTimer(2, 0);
	moveBalls->SetFuncPointer(MovePongBall);
	moveBalls->start();
	main->funcTimers.push_back(moveBalls);
	Box* paddle1 = main->shapes->AddBox(-2, 0, 1, Color::getBlue(), 2, .5);
	paddle1->addTag(Tag::Unscorable);
	Box* paddle2 = main->shapes->AddBox(2, 0, 1, Color::getRed(), 2, .5);
	paddle2->addTag(Tag::Unscorable);
	main->shapes->AddRectBarrier(0, -5, 20, 1);
	main->shapes->AddRectBarrier(1, 5, 20, 1);
	left = main->shapes->buildGoal(-5, 0,1,100, Color::getGreen(), "left");
	right = main->shapes->buildGoal(5, 0,1,100, Color::getGreen(), "right");

	main->keyboardFunc = DoNothing;
	scenes["main"] = main;
	currentScene = instructions;

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("haha u lost");
	scenes["gameOver"] = gameOver;
}

void PongLevel::update()
{
	Level::update();
	if (right->score > 0 || left->score > 0)
	{
		if (currentScene == scenes["main"])
		{
			sf::String loser;
			if (right->score > 0)
				loser = "right";
			else
				loser = "left";
			scenes["gameOver"]->ui.labels.erase(scenes["gameOver"]->ui.labels.begin());
			scenes["gameOver"]->ui.buildLabel("The player on the " + loser + " is weaker!", 0, 0, 30);
		}
		currentScene = scenes["gameOver"];
	}
}

