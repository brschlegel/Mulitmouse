#include "FuncTimerFunctions.h"

void spawnKinematicBox(Scene* scene)
{
	Box* b = scene->world.AddBox(0, 2, 1, Color::getRed(), .5, .5);
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
	scene->world.AddBox(-6, 3, 1, Color::getRed(), .5, .5);
	scene->world.AddBox(6, 3, 1, Color::getBlue(), .5, .5);
}