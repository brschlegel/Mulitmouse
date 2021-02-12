#include "CollisionManager.h"

CollisionManager::CollisionManager(PhysicsWorld* world, MouseManager* mouseManager)
{
	this->world = world;
	this->mouseManager = mouseManager;
	drawDebugFlag = true;
}

Goal* CollisionManager::buildGoal(float x, float y, Color color)
{
	Goal* g = new Goal(x, y, color);
	triggers.push_back(g);
	return g;
}

Goal* CollisionManager::buildGoal(float x, float y, float width, float height, Color color)
{
	Goal* g = new Goal(x, y, color,width,height);
	triggers.push_back(g);
	return g;
}

void CollisionManager::update()
{
	//bodies check
	for (unsigned int j = 0; j < world->bodies.size(); j++)
	{

		b2AABB b;
		b2Transform bt = world->bodies[j]->body->GetTransform();
		//mice
		for (unsigned int i = 0; i < mouseManager->mice.size(); i++)
		{
			b2AABB a;
			b2Transform t;
			t.Set(b2Vec2(mouseManager->mice[i]->x, mouseManager->mice[i]->y), 0);
			mouseManager->mice[i]->shape.ComputeAABB(&a, t, 0);


			world->bodies[j]->shape.ComputeAABB(&b, bt, 0);
			if (b2TestOverlap(a, b))
			{
				//if left clicking on a physics object
				if (mouseManager->mice[i]->leftButtonPressed && world->bodies[j]->body->GetType() == b2_dynamicBody && mouseManager->mice[i]->physicsSelect == NULL)
				{	
					world->bodies[j]->body->SetType(b2_kinematicBody);
					world->bodies[j]->body->SetLinearVelocity(b2Vec2_zero);
					world->bodies[j]->selected = true;
					mouseManager->mice[i]->physicsSelect = world->bodies[j];
				}
			}
		}


		//Triggers
		for (int i = 0; i < triggers.size(); i++)
		{
			
			b2AABB triggerAABB;
			b2Transform triggerTransform;
			

			if (triggers[i]->physicsTrigger  && world->bodies[j]->body->GetType() != b2_staticBody )
			{
				//Goals
				if (triggers[i]->triggerId == 1)
				{
					triggerTransform.Set(b2Vec2(triggers[i]->x, triggers[i]->y), 0);
					triggers[i]->shape.ComputeAABB(&triggerAABB, triggerTransform, 0);
					if (b2TestOverlap(b, triggerAABB))
					{
						triggers[i]->onEnter(world->bodies[j]);
						world->deleteObject(j);
						
					}
				}

			}
		}
	}
}

void CollisionManager::draw()
{
	for (int i = 0; i < triggers.size(); i++)
	{
		triggers[i]->draw();
		if (drawDebugFlag)
		{
			triggers[i]->drawDebug();
		}
	}

}
