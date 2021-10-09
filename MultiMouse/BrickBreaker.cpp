#include "BrickBreaker.h"
#include "PongLevel.h"

BrickBreaker::BrickBreaker()
{
	Scene* instructions = new Scene(standardGravity, "instructions");
	instructions->buildInstructionScene("BrickBreaker", "Break as many bricks as possible", "BrickBreaker");
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	main->shapes->world->SetContactListener(&listener);
	bottomCage = main->shapes->buildCage(0, -3,18,3,Color::getBlue());
	main->initDel.BindLambda([this]() {
		bottomCage->init();
		}
	);

	ball = main->shapes->buildGoal(0,-3,.25,.25,Color::getGreen());
	paddle = main->shapes->AddBox(-1,-4,0,Color::getRed(), 0.5, 2);
	paddle->addTag(Tag::Unscorable);
	paddle->body->SetType(b2_staticBody);
	paddle->body->SetGravityScale(0);
	hidden = main->shapes->AddBox(0,-3,1,Color::getGreen(),0.2,0.2);
	hidden->addTag(Tag::Unscorable);
	hidden->body->SetType(b2_dynamicBody);
	hidden->addTag(Tag::Pong);
	hidden->body->SetGravityScale(0);
	brick = main->shapes->AddBox(3,3,0,Color::getBlue(),0.5,0.5);
	main->frameScene();
	scenes["main"] = main;
	currentScene = scenes["instructions"];

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("You won");
	scenes["gameOver"] = gameOver;

	
}

void BrickBreaker::update()
{
	Level::update();
	ball->x = hidden->x;
	ball->y = hidden->y;
	if (ball->score>0)
	{
		MouseManager::getInstance()->resetBounds();
		currentScene = scenes["gameOver"];
	}
}

void BrickBreaker::init()
{
	
	//bottomCage->AddMouse();
}
