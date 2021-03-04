#include "CollisionManager.h"

CollisionManager::CollisionManager(PhysicsWorld* world, MouseManager* mouseManager)
{
	this->world = world;
	this->mouseManager = mouseManager;
	drawDebugFlag = true;
	
}

CollisionManager::CollisionManager()
{
	world = nullptr;
	mouseManager = nullptr;
	drawDebugFlag = false;
}

Goal* CollisionManager::buildGoal(float x, float y, Color color, std::string name)
{
	Goal* g = new Goal(x, y, color, name);
	triggers.push_back(g);
	return g;
}

Goal* CollisionManager::buildGoal(float x, float y, float width, float height, Color color, std::string name)
{
	Goal* g = new Goal(x, y, color,width,height, name);
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
		world->bodies[j]->shape.ComputeAABB(&b, bt, 0);

		//mice
		for (unsigned int i = 0; i < mouseManager->mice.size(); i++)
		{
			b2AABB a;
			b2Transform t;
			t.Set(b2Vec2(mouseManager->mice[i]->x, mouseManager->mice[i]->y), 0);
			mouseManager->mice[i]->shape.ComputeAABB(&a, t, 0);
			
			if (b2TestOverlap(a, b))
			{
				//if left clicking on a physics object
				if (mouseManager->mice[i]->leftButtonPressed && world->bodies[j]->body->GetType() == b2_dynamicBody && mouseManager->mice[i]->physicsSelect == NULL && world->bodies[j]->selectable)
				{	
					world->bodies[j]->body->SetType(b2_kinematicBody);
					world->bodies[j]->body->SetLinearVelocity(b2Vec2_zero);
					world->bodies[j]->selected = mouseManager->mice[i];
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
				if (triggers[i]->triggerId == 1 && !world->bodies[j]->hasTag(Tag::Unscorable))
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

Trigger* CollisionManager::getTriggerByName(std::string name)
{
	for (Trigger* trigger : triggers)
	{
		if (trigger->name == name)
			return trigger;
	}
	return nullptr;
}
