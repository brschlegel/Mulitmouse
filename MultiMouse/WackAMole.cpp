#include "WackAMole.h"

int score = 0;
ClickedMouseGoal* mole;
Mouse* winner;
WackAMole::WackAMole()
{
	Scene* instructions = new Scene(standardGravity, "Instructions");
	instructions->buildInstructionScene("WackAMole", "Click the green box before it disappears", "WackAMole");
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	startingPosition = b2Vec2(0, -4.5f);
	FuncTimer* spawnBoxTimer = new FuncTimer(5, -3, 10, "SpawnBox");
	spawnBoxTimer->del.BindLambda([main]() {
		mole = main->shapes->buildClickedMouseGoal(-(rand() % 1600 - 800) / 100.0f, (rand() % 1000 - 500) / 100.0f, 2, 2, Color::getGreen());
		mole->onClickDel.BindLambda([](Mouse* m)
			{
				ScoreManager::getInstance()->incrementScore(m);
				winner = m;
			});
	});
	main->funcTimers.push_back(spawnBoxTimer);
	FuncTimer* deleteBoxTimer = new FuncTimer(5,-1, 10 , "DeleteBox");
	deleteBoxTimer->del.BindLambda([main]() {
		
		main->shapes->deleteObject(mole);
		});
	main->funcTimers.push_back(deleteBoxTimer);
	
	scenes["main"] = main;

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("You won!");
	scenes["gameOver"] = gameOver;

	currentScene = scenes["instructions"];
}

void WackAMole::update()
{
	Level::update();
	if (currentScene->name == "main")
	{
		if (mole != nullptr &&  mole->numClicks > 0) {
			currentScene = scenes["gameOver"];
			scenes["gameOver"]->ui.labels.erase(scenes["gameOver"]->ui.labels.begin());
			scenes["gameOver"]->ui.buildLabel("Player #" + winner->text.getString() + " wins!", 0, 0, 30);
		}
		
	}
}