#include "MazeLevel.h"

vector<string> levels = { "First", "Righty" };

MazeLevel::MazeLevel()
{
	mouseNum = -2;
	Scene* instructions = new Scene(standardGravity, "Instructions");
	instructions->buildInstructionScene("Maze", "Work with your team to solve the maze before your opponents. The box will be situated at the center of your teams mice, left click to increase your influence!", "Maze");
	scenes["instructions"] = instructions;

	scenes["main"] = new  Scene(standardGravity, "Main");
	Scene* main = scenes["main"];
	left = scenes["main"]->shapes->buildGoal(-5, 4, 3,.5 ,Color::getRed(), "left");
	right = scenes["main"]->shapes->buildGoal(5, 4, 3, .5, Color::getRed(), "right");
	main->frameScene();
	//Seperate two sides
	main->shapes->AddRectBarrier(0, 0, .5, 10);
	
	//Select Random Level

	int levelID = rand() % levels.size();
	//int levelID = 1;
	Structure s = Structure("Mazes/" + levels[levelID], .5f);
	s.buildStructure(main->shapes, b2Vec2(4.5,-.5));
	s.buildStructure(main->shapes, b2Vec2(-4.5, -.5));
	//Add COM Boxes
	COMBox* lBox  = main->shapes->buildCOMBox(-3, -4, .3f, .3f, MouseManager::getInstance()->teams[0][0]->teamColor);
	lBox->setTeam(MouseManager::getInstance()->teams[0]);
	COMBox* rBox = main->shapes->buildCOMBox(3, -4, .3f, .3f, MouseManager::getInstance()->teams[1][0]->teamColor);
	rBox->setTeam(MouseManager::getInstance()->teams[1]);

	//Add mouse cages
	cages.push_back(main->shapes->buildCage(-8.5, 0, .5f, 9, Color::getRed()));
	cages.push_back(main->shapes->buildCage(-.5f, 0, .5f, 9, Color::getRed()));
	cages.push_back(main->shapes->buildCage(.5f, 0, .5f, 9, Color::getRed()));
	cages.push_back(main->shapes->buildCage(8.5, 0, .5f, 9, Color::getRed()));

	main->initDel.BindLambda([this]()
		{
			for (int i = 0; i < cages.size(); i++)
			{
				cages[i]->init();
			}
		});


	currentScene = scenes["instructions"];

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("haha u lost");
	scenes["gameOver"] = gameOver;
}

void MazeLevel::update()
{
	Level::update();
	if (left->score > 0)
	{
		MouseManager::getInstance()->resetBounds();
		currentScene = scenes["gameOver"];
		currentScene->ui.labels.erase(currentScene->ui.labels.begin());
		currentScene->ui.buildLabel("Left team wins!", 0, 0, 30);
	}
	else if (right->score > 0)
	{
		MouseManager::getInstance()->resetBounds();
		currentScene = scenes["gameOver"];
		currentScene->ui.labels.erase(currentScene->ui.labels.begin());
		currentScene->ui.buildLabel("Right team wins!", 0, 0, 30);
	}
}

void MazeLevel::init()
{
	int perTeam = MouseManager::getInstance()->teams[0].size() / 2;
	vector<Mouse*> leftTeam = MouseManager::getInstance()->teams[0];
	vector<Mouse*> rightTeam = MouseManager::getInstance()->teams[1];
	for (int i = 0; i < leftTeam.size(); i++)
	{
		if (i < perTeam)
		{
			cages[0]->AddMouse(leftTeam[i]);
		}
		else
		{
			cages[1]->AddMouse(leftTeam[i]);
		}
	}

	for (int i = 0; i < rightTeam.size(); i++)
	{
		if (i < perTeam)
		{
			cages[2]->AddMouse(rightTeam[i]);
		}
		else
		{
			cages[3]->AddMouse(rightTeam[i]);
		}
	}
}
