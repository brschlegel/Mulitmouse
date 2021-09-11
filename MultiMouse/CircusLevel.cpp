#include "CircusLevel.h"

CircusLevel::CircusLevel()
{
	Scene* instructions = new Scene(standardGravity, "Instructions");
	instructions->buildInstructionScene("Circus", "Get to the end of the maze without touching any of the walls", "Circus");
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	startingPosition = b2Vec2(0, -4);
	//goals.push_back(main->shapes->buildMouseGoal(0, 0, 1, 1, Color::getBlue()));
	Structure s = Structure("Mazes/First", .5f);
	s.buildStructure(main->shapes, b2Vec2(0, 0));
	scenes["main"] = main;

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("haha u lost");
	scenes["gameOver"] = gameOver;

	currentScene = scenes["instructions"];
}

void CircusLevel::update()
{
	Level::update();
	for (MouseGoal* goal : goals)
	{
		for (Mouse* mouse : goal->mice)
		{
			mouse->frozen = false;
			mouse->x = startingPosition.x;
			mouse->y = startingPosition.y;
		}
		goal->mice.clear();
	}
}
