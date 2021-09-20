#include "CubicBezier.h"

CubicBezier::CubicBezier(Color color, int LOD, int mask, std::string name) : Line(color, LOD, mask, name)
{
	//Adding one more to cover gaps
	points.push_back(LinePoint());
}

void CubicBezier::addControlPoint(PolygonObject* obj)
{
	controlPoints.push_back(obj);
}

void CubicBezier::update()
{
	placePoints();
}

void CubicBezier::placePoints()
{
	//b2Vec2 p1 = b2Vec2(controlPoints[0]->x, controlPoints[0]->y);
	//b2Vec2 p2 = b2Vec2(controlPoints[1]->x, controlPoints[1]->y);
	//b2Vec2 p3 = b2Vec2(controlPoints[2]->x, controlPoints[2]->y);
	//b2Vec2 p4 = b2Vec2(controlPoints[3]->x, controlPoints[3]->y);
	//float tStep = 1.0f / LOD;
	//float t = 0;
	//for (int i = 0; i < LOD;i++ )
	//{
	//	t += tStep;
	//	b2Vec2 a = std::pow(1 - t, 3) * p1;
	//	b2Vec2 b = std::pow(1 - t, 2) * 3 * t *p2;
	//	b2Vec2 c = (1-t) * std::pow(t, 2) * 3 * p3;
	//	b2Vec2 d = std::pow(t, 3) * p4;
	//	points[i].position = a + b + c + d;
	//}

	//One of these days ill stop being lazy and transfer over to b2Vec2 permenantly
	std::vector<b2Vec2> p;
	std::vector<float> coeff;
	
	for (int i = 0; i < controlPoints.size(); i++)
	{
		p.push_back(b2Vec2(controlPoints[i]->x, controlPoints[i]->y));
	
	}
	float tStep = 1.0f / LOD;
	float t = 0;
	float n = controlPoints.size() - 1;

	points[0].position = p[0];
	for (int i = 1; i < LOD -1 ; i++)
	{
		b2Vec2 pos = b2Vec2(0, 0);
		t += tStep;
		for (int j = 0; j < controlPoints.size(); ++j)
		{
			pos += BenMath::binomialCoefficients(n, j)* ( std::pow((1 - t), (n - j)))* std::pow(t, j) * p[j];
		}
		
		points[i].position = pos;
	}
	points[LOD - 1].position = p[n];
}
