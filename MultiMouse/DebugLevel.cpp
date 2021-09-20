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
	Bezier* bezier = scenes["main"]->shapes->buildBezier(Color::getRed(), 100, 4);
	bezier->addControlPoint(main->shapes->buildControlPoint(b2Vec2(5, -3), Color::getBlue()));
	bezier->addControlPoint(MouseManager::getInstance()->getActiveMice()[0]);
	bezier->addControlPoint(MouseManager::getInstance()->getActiveMice()[1]);
	bezier->addControlPoint(MouseManager::getInstance()->getActiveMice()[2]);
	bezier->addControlPoint(MouseManager::getInstance()->getActiveMice()[3]);
	bezier->addControlPoint(main->shapes->buildControlPoint(b2Vec2(-5, 3), Color::getBlue()));

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

