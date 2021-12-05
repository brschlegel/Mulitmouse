#include "CircusLevel.h"

CircusLevel::CircusLevel()
{
	Scene* instructions = new Scene(standardGravity, "Instructions");
	instructions->buildInstructionScene("Circus", "Get to the end of the maze without touching any of the walls", "Circus");
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	startingPosition = b2Vec2(0, -4.75f);
	
	Structure s = Structure("CircusMazes/First", .5f);
	s.buildStructure(main->shapes, b2Vec2(0, 0));
	//Adding all the goals to the list
	for (PolygonObject* obj : s.objects)
	{
		MouseGoal* goal = dynamic_cast<MouseGoal*>(obj);
		goals.push_back(goal);
	}
	
	finish = main->shapes->buildMouseGoal(0, 5, 2, 1, Color::getBlue());
	scenes["main"] = main;

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("haha u won");
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

	if (finish->mice.size() > 0 && currentScene == scenes["main"])
	{
		currentScene = scenes["gameOver"];
		for (Mouse* m : finish->mice)
		{
			m->frozen = false;
			ScoreManager::getInstance()->incrementScore(m);
		}
		scenes["gameOver"]->ui.labels.erase(scenes["gameOver"]->ui.labels.begin());
		scenes["gameOver"]->ui.buildLabel("Player #" + finish->mice[0]->text.getString() + " wins!", 0, 0, 30);

	}
}
