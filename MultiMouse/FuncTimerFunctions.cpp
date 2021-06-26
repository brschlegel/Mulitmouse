#include "FuncTimerFunctions.h"

void spawnKinematicBox(Scene* scene)
{
	Box* b = scene->shapes->AddBox(0, 2, 1, Color::getRed(), .5, .5);
	b->body->SetType(b2_kinematicBody);
	b->addTag(Tag::Ball);

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
	scene->shapes->AddBox(-6, 3, 1, Color::getRed(), .5, .5);
	scene->shapes->AddBox(6, 3, 1, Color::getBlue(), .5, .5);
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
