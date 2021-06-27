#include "FuncTimerFunctions.h"

void spawnKinematicBox(Scene* scene)
{


}

void setBallDynamic(Scene* scene)
{
	for(PolygonPhysicsObject* ball : scene->getBodyByTag(Tag::Ball))
	{
		if (ball->body->GetType() != b2_dynamicBody)
		{
			ball->body->SetType(b2_dynamicBody);
		}
	}
}

void MovePongBall(Scene* scene)
{

	for (PolygonPhysicsObject* b : scene->getBodyByTag(Tag::Pong))
	{
		b->body->SetType(b2_dynamicBody);
		float x = (float)((rand() % 100) - 50) / 20;
		float y = (float)((rand() % 100) - 50) / 20;
		b->body->SetLinearVelocity(b2Vec2(x,y));
	}
}

void SpawnDodgeBox(Scene* scene)
{

}

void turnMiceInvisible(Scene* scene)
{
	vector<Mouse*> activeMice = MouseManager::getInstance()->getActiveMice();
	for (int i = 0; i < activeMice.size(); i++)
	{
		activeMice[i]->drawn = false;
	}
}

void turnMiceVisible(Scene* scene)
{
	vector<Mouse*> activeMice = MouseManager::getInstance()->getActiveMice();
	for (int i = 0; i < activeMice.size(); i++)
	{
		activeMice[i]->drawn = true;
	}
}
