#include "LevelSelect.h"

LevelSelect::LevelSelect()
{
	Scene* main = new Scene(standardGravity, "main");
	LevelButton* dodgeball = main->collisions.buildLevelButton(-1, -1, 1.5f, .5f, Color::getRed(), LevelName::Dodgeball);
	main->collisions.buildLevelButton(2, 1, 1, .5f, Color::getBlue(), LevelName::DebugLevel);
	for (int i = 0; i < dodgeball->vertices.size(); i++)
	{
		cout << "original: " << "x: " << dodgeball->vertices[i].x << "y: " << dodgeball->vertices[i].y << endl;
		sf::Vector2<int> vec = main->ui.convertWorldToUI(dodgeball->vertices[i].x * 2, dodgeball->vertices[i].y * 2);
		cout << "new: " << "x: " << vec.x << "y: " << vec.y << endl;
		cout << "-=============-" << endl;
		
	}
	main->ui.buildLabelInTrigger("Dodgeball", dodgeball);


	main->frameScene();
	scenes["main"] = main;
	currentScene = scenes["main"];
}

void LevelSelect::update()
{
	currentScene->update();
}
