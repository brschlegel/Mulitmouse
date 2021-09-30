#include <ClickRace.h>

ClickRace::ClickRace() 
{
	Scene* instructions = new Scene(standardGravity, "Instructions");
	instructions->buildInstructionScene("Clicking Race", "Click the your box as fast as you can to win", "ClickingRace");
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	goal = main->shapes->buildGoal(0,5,2,2,Color::getGreen());
	clickButton = main->shapes->buildClickedMouseGoal(-5,0,1,1,Color::getBlue());
	runner = main->shapes->AddBox(-0.5, 0, 1, Color::getBlue(), 1,1);
	runner2 = main->shapes->AddBox(0.5, 0, 1, Color::getRed(), 1, 1);
	runner->body->SetType(b2_kinematicBody);
	runner2->body->SetType(b2_kinematicBody);
	scenes["main"] = main;

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("You won!");
	scenes["gameOver"] = gameOver;

	currentScene = scenes["instructions"];
}

void ClickRace::update()
{
	Level::update();
	
	if (currentScene->name == "main")
	{
		if (clickButton->numClicks > 0) {
			runner->body->SetLinearVelocity(b2Vec2(0, 3));
			clickButton->numClicks = 0;
		}
		else
		{
			runner->body->SetLinearVelocity(b2Vec2(0, 0));
		}
		if (goal->score > 0)
		{
			currentScene = scenes["gameOver"];
		}
	}
}