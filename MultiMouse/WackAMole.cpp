#include "WackAMole.h"

WackAMole::WackAMole()
{
	Scene* instructions = new Scene(standardGravity, "Instructions");
	instructions->buildInstructionScene("WackAMole", "Click the green box before it disappears", "WackAMole");
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	startingPosition = b2Vec2(0, -4.5f);
	FuncTimer* spawnBoxTimer = new FuncTimer(5, -3, 10, "SpawnBox");
	spawnBoxTimer->del.BindLambda([main]() {

		});
	finish = main->shapes->buildMouseGoal(0, 5, 2, 1, Color::getBlue());
	scenes["main"] = main;

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("You won!");
	scenes["gameOver"] = gameOver;

	currentScene = scenes["instructions"];
}

void WackAMole::update()
{
	Level::update();
}