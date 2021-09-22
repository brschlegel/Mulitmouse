#include "CurveMatch.h"

Color transparent = Color(1, 1, 1, 0);
CurveMatch::CurveMatch()
{
	Scene* instructions = new Scene(standardGravity, "instructions");
	instructions->buildInstructionScene("Curve Match", "In curve match, each mouse is a control point on a bezier curve. The first and last control points along the curve are marked by the red triangles. Your curve is red, the curve you are attempting to emulate is blue. When you get close enough, a new curve will appear. Do as many as you can within the time limit!", "CurveMatch");
	currentScene = instructions;
	scenes["instructions"] = instructions;
	numMice = MouseManager::getInstance()->getNumOfActiveMice();

	Scene* main = new Scene(standardGravity, "main");
	playerCurve = main->shapes->buildBezier(Color::getRed(), 200, 0);
	playerCurve->addControlPoint(main->shapes->buildControlPoint(b2Vec2(5, -3), Color::getRed()));
	for (int i = 0; i < numMice; i++)
	{
		playerCurve->addControlPoint(MouseManager::getInstance()->mice[i]);
	}
	playerCurve->addControlPoint(main->shapes->buildControlPoint(b2Vec2(-5, 3), Color::getRed()));
	
	gameCurve = main->shapes->buildBezier(Color::getBlue(), 200, 0);
	gameCurve->addControlPoint(main->shapes->buildControlPoint(b2Vec2(5, -3), transparent));
	for (int i = 0; i < numMice; i++)
	{
		gameCurve->addControlPoint(main->shapes->buildControlPoint(generateControlPoint(), transparent));
	}
	gameCurve->addControlPoint(main->shapes->buildControlPoint(b2Vec2(-5, 3),transparent));
	
	scenes["main"] = main;

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("Nice Job!");
	scenes["gameOver"] = gameOver;

}

void CurveMatch::update()
{
	Level::update();

}

b2Vec2 CurveMatch::generateControlPoint()
{
	float x = (rand() % 1600 - 800) / 100.0f;


	float y = (rand() % 1000 - 500) / 100.0f;
	return b2Vec2(x,y);
}

void CurveMatch::generateNewCurve()
{

}
