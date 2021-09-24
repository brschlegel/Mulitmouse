#pragma once
#include "Level.h"
class CurveMatch :
	public Level
{
public:
	CurveMatch();
	Bezier* playerCurve;
	Bezier* gameCurve;
	int numMice;
	void update();
	void generateNewCurve();
	b2Vec2 generateControlPoint();
	int score;
	Timer* timer;
	float threshold;


};

