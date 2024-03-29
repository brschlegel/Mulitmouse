#include <ClickRace.h>

ClickRace::ClickRace() 
{
	Scene* instructions = new Scene(standardGravity, "Instructions");
	instructions->buildInstructionScene("Clicking Race", "Click the your box as fast as you can to win", "ClickingRace");
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	goal = main->shapes->buildGoal(0,5,2,2,Color::getGreen());
	goal->onColDel.BindLambda([this](PolygonObject* box)
		{
			ScoreManager::getInstance()->incrementScoreTeam(MouseManager::getInstance()->getTeamByColor(box->color));
			scenes["gameOver"]->ui.labels.erase(scenes["gameOver"]->ui.labels.begin());
			if (box->color == Color::getRed())
			{
				scenes["gameOver"]->ui.buildLabel("Red team wins!", 0, 0, 30);
			}
			else
			{
				scenes["gameOver"]->ui.buildLabel("Blue team wins!", 0, 0, 30);
			}
			
		});
	clickButton = main->shapes->buildClickedMouseGoal(5,0,1,1,Color::getBlue());
	clickButton2 = main->shapes->buildClickedMouseGoal(-5, 0, 1, 1, Color::getRed());
	runner = main->shapes->AddBox(0.5, 0, 1, Color::getBlue(), 1,1);
	runner2 = main->shapes->AddBox(-0.5, 0, 1, Color::getRed(), 1, 1);
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
		if (goal->score > 0)
		{
			currentScene = scenes["gameOver"];

			return;
		}
		if (clickButton->numClicks > 0) {
			runner->body->SetLinearVelocity(b2Vec2(0, 3));
			clickButton->numClicks = 0;
		}
		else
		{
			runner->body->SetLinearVelocity(b2Vec2(0, 0));
		}
		if (clickButton2->numClicks>0)
		{
			runner2->body->SetLinearVelocity(b2Vec2(0, 3));
			clickButton2->numClicks = 0;
		}
		else
		{
			runner2->body->SetLinearVelocity(b2Vec2(0,0));
		}
	}
}