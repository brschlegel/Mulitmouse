#include "AngryBirds.h"
#include "KeyboardFunctions.h"

AngryBirds::AngryBirds() {
	Scene* instructions = new Scene(standardGravity, "instructions");
	instructions->buildInstructionScene("BasketBall", "Put the Ball in the basket", "BasketBall");
	scenes["instructions"] = instructions;

	Scene* main = new Scene(standardGravity, "main");
	//main->shapes->world->SetContactListener(&listener);
	leftCage = main->shapes->buildCage(-7, 0, 4, 10, Color::getBlue());
	main->initDel.BindLambda([this]() {
		leftCage->init();
		}
	);
	basket = main->shapes->buildGoal(5, 0, .5f, .5f, Color::getBlue());
	ball = main->shapes->AddBox(-6, -4, 0, Color::getGreen(), 0.5, 0.5);
	ball->body->SetType(b2_dynamicBody);
	main->frameScene();
	scenes["main"] = main;
	currentScene = scenes["instructions"];

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("You won");
	scenes["gameOver"] = gameOver;
}

void AngryBirds::update() {
	Level::update();
	if (basket->score > 0) {
		MouseManager::getInstance()->resetBounds();
		currentScene = scenes["gameOver"];
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		MouseManager::getInstance()->resetBounds();
		currentScene = scenes["gameOver"];
	}
}

void AngryBirds::init() {
	leftCage->AddMouse(MouseManager::getInstance()->getActiveMice()[0]);
}