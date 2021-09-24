#include "CurveMatch.h"

Color transparent = Color(1, 1, 1, 0);


CurveMatch::CurveMatch()
{
	Scene* instructions = new Scene(standardGravity, "instructions");
	instructions->buildInstructionScene("Curve Match", "In curve match, each mouse is a control point on a bezier curve. The first and last control points along the curve are marked by the red triangles. Your curve is red, the curve you are attempting to emulate is blue. When you get close enough, a new curve will appear. Do as many as you can within the time limit!", "CurveMatch");
	currentScene = instructions;
	scenes["instructions"] = instructions;
	numMice = MouseManager::getInstance()->getNumOfActiveMice();
	threshold = .25f * numMice;
	Scene* main = new Scene(standardGravity, "main");
	timer = main->ui.buildTimer(30, 0, 4, 30);
	
	//Curve to be matched
	Color gameCurveColor = Color::getBlue();
	gameCurveColor.a = .5f;
	gameCurve = main->shapes->buildBezier(gameCurveColor, 200, 0);
	gameCurve->addControlPoint(main->shapes->buildControlPoint(b2Vec2(5, -3), transparent));
	for (int i = 0; i < numMice; i++)
	{
		gameCurve->addControlPoint(main->shapes->buildControlPoint(generateControlPoint(), transparent));
	}
	gameCurve->addControlPoint(main->shapes->buildControlPoint(b2Vec2(-5, 3),transparent));

	//Players curve
	playerCurve = main->shapes->buildBezier(Color::getRed(), 200, 0);
	playerCurve->addControlPoint(main->shapes->buildControlPoint(b2Vec2(5, -3), Color::getRed()));
	for (int i = 0; i < numMice; i++)
	{
		playerCurve->addControlPoint(MouseManager::getInstance()->mice[i]);
	}
	playerCurve->addControlPoint(main->shapes->buildControlPoint(b2Vec2(-5, 3), Color::getRed()));
	
	scenes["main"] = main;

	Scene* gameOver = new Scene(standardGravity, "gameOver");
	gameOver->buildGameOverScene("Nice Job!");
	scenes["gameOver"] = gameOver;

}

void CurveMatch::update()
{
	Level::update();
	int numCorrect = 0;
	if (currentScene->name == "main")
	{
		for (int i = 0; i < gameCurve->points.size(); i++)
		{
			float distance = b2Distance(gameCurve->points[i].position, playerCurve->points[i].position);
			if (distance < threshold)
			{
				numCorrect++;
				playerCurve->points[i].color = Color::getGreen();
			}
			else
			{
				playerCurve->points[i].color = Color::getRed();
			}
		}
		if (numCorrect == gameCurve->points.size())
		{
			generateNewCurve();
			score++;
		}
		if (timer->getNumSeconds() < 0)
		{
			scenes["gameOver"]->ui.buildLabel("Score: " + to_string(score), 0, -1, 24);
			currentScene = scenes["gameOver"];
		}
	}

}

b2Vec2 CurveMatch::generateControlPoint()
{
	float x = (rand() % 1600 - 800) / 100.0f;


	float y = (rand() % 1000 - 500) / 100.0f;
	return b2Vec2(x,y);
}

void CurveMatch::generateNewCurve()
{
	for (int i = 0; i < numMice; i++)
	{
		b2Vec2 newPoint = generateControlPoint();
		gameCurve->controlPoints[i + 1]->x = newPoint.x;
		gameCurve->controlPoints[i + 1]->y = newPoint.y;

	}
}
