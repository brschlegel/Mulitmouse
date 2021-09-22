#include "DebugLevel.h"
#include "KeyboardFunctions.h"
DebugLevel::DebugLevel()
{
	mouseNum = 0;
	Scene* instructions = new Scene(standardGravity, "Instructions");
	instructions->buildInstructionScene("DebugLevel", "This is the sandbox level!Press b on the keyboard to spawn a box to play with. Throwing the box into the green goal will make it disappear!", "DebugLevel");
	scenes["instructions"] = instructions;

	scenes["main"]= new  Scene(standardGravity, "Main");

	scenes["main"]->frameScene();
	Scene* main = scenes["main"];
	Box* b = scenes["main"]->shapes->AddBox(0, 4, 1, Color::getRed(), 1.0f, 1.0f);
	scenes["main"]->shapes->AddRectBarrier(0, 0, 1, 1);
	
	scenes["main"]->shapes->buildGoal(-2, 2, 1, 1, Color::getGreen());
	scenes["main"]->keyboardFunc = DebugLevelKeyboard;
	ClickedMouseGoal* m = main->shapes->buildClickedMouseGoal(0, 3, 1, 1, Color::getBlue());

	currentScene = scenes["instructions"]; 
}

void DebugLevel::draw(sf::RenderWindow* window) 
{
	currentScene->draw(window);
}

void DebugLevel::update()
{
	
	if (currentScene ==  scenes["instructions"] && scenes["instructions"]->readyUpButton->checkFull())
	{
		MouseManager::getInstance()->unfreezeAllMice();
		currentScene = scenes["main"];
	}
	currentScene->update();
	
}

