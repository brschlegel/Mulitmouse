#include "PongLevel.h"

PongLevel::PongLevel()
{
	
	Scene* main = new Scene(standardGravity, "main");

	Scene* instructions = new Scene(standardGravity, "instructions");
	instructions->buildInstructionScene("Pong", "Ah the classic game Pong. Except you have to actively hold the paddles, and you can move them wherever you want. And there are multiple balls. And the physics are wackier. Whatever, just don't lose", "Pong");
	scenes["instructions"] = instructions;

	main->shapes->world->SetContactListener(&listener);
	for (int i = 0; i < 1; i++)
	{
		Box* b = main->shapes->AddBox(0, 2, 1, Color::getBlue(), .2, .2);
		b->selectable = false;
		b->body->SetGravityScale(0);
		b->body->SetType(b2_kinematicBody);
		b->addTag(Tag::Pong);
	}
	FuncTimer* moveBalls = new FuncTimer(2, 0);
	moveBalls->del.BindLambda([main]()
		{
			for (PolygonPhysicsObject* b : main->getBodyByTag(Tag::Pong))
			{
				b->body->SetType(b2_dynamicBody);
				float x = (float)((rand() % 100) - 50) / 20;
				float y = (float)((rand() % 100) - 50) / 20;
				b->body->SetLinearVelocity(b2Vec2(x, y));
			}
		}
			);
	//moveBalls->start();
	main->funcTimers.push_back(moveBalls);
	//team one
	auto teams = MouseManager::getInstance()->teams;
	for (int i = 0; i < teams[0].size(); i++)
	{
		Box* paddle = main->shapes->AddBox(-2 + (i), 0, 1, teams[0][0]->color, 2, .5);
		paddle->addTag(Tag::Unscorable);
		left = main->shapes->buildGoal(-9, 0, 1, 100, teams[0][0]->color, "left");
	}

	//team two 
	for (int i = 0; i < teams[1].size(); i++)
	{
		Box* paddle = main->shapes->AddBox(2 + (i), 0, 1, teams[1][0]->color, 2, .5);
		paddle->addTag(Tag::Unscorable);
		right = main->shapes->buildGoal(9, 0, 1, 100, teams[1][0]->color, "right");
	}
	main->shapes->AddRectBarrier(0, -5, 20, 1);
	main->shapes->AddRectBarrier(1, 5, 20, 1);


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
			{
				loser = "Blue";
				ScoreManager::getInstance()->incrementScoreTeam(MouseManager::getInstance()->getTeamByColor(left->color));
			}
			else
			{
				loser = "Red";
				ScoreManager::getInstance()->incrementScoreTeam(MouseManager::getInstance()->getTeamByColor(right->color));
			}
			scenes["gameOver"]->ui.labels.erase(scenes["gameOver"]->ui.labels.begin());
			scenes["gameOver"]->ui.buildLabel( loser + " team is weaker!", 0, 0, 30);
		}
		currentScene = scenes["gameOver"];
	}
}

