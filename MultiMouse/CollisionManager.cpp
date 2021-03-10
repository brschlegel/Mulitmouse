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

MouseCage* CollisionManager::buildCage(float x, float y, Color color, std::string name)
{
	color.a = .5f;
	MouseCage* cage = new MouseCage(x, y, color, name);
	triggers.push_back(cage);
	return cage;
}

MouseCage* CollisionManager::buildCage(float x, float y, float width, float height, Color color, std::string name)
{
	color.a = .5f;
	MouseCage* cage = new MouseCage(x, y, width, height, color, name);
	triggers.push_back(cage);
	return cage;
}

void CollisionManager::unload()
{
	for (int i = 0; i < triggers.size(); i++)
	{
		delete triggers[i];
	}
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


		//Triggers with boxes
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

	//Mice with triggers
	for (unsigned int i = 0; i < mouseManager->mice.size(); i++)
	{
		b2AABB a;
		b2Transform t;
		t.Set(b2Vec2(mouseManager->mice[i]->x, mouseManager->mice[i]->y), 0);
		mouseManager->mice[i]->shape.ComputeAABB(&a, t, 0);

		for (unsigned int j = 0; j < triggers.size(); j++)
		{

			b2AABB triggerAABB;
			b2Transform triggerTransform;
			triggerTransform.Set(b2Vec2(triggers[i]->x, triggers[i]->y), 0);
			triggers[i]->shape.ComputeAABB(&triggerAABB, triggerTransform, 0);
		}

	}

	//MouseCages
	for (unsigned int i = 0; i < triggers.size(); i++)
	{
		
		if (triggers[i]->triggerId == 2)
		{
			MouseCage* cage = dynamic_cast<MouseCage*>(triggers[i]);
			b2AABB triggerAABB;
			b2Transform triggerTransform;
			triggerTransform.Set(b2Vec2(triggers[i]->x, triggers[i]->y), 0);
			triggers[i]->shape.ComputeAABB(&triggerAABB, triggerTransform, 0);
			for (Mouse* mouse : cage->mice)
			{
				b2AABB m;
				b2Transform mt;
				mt.Set(b2Vec2(mouse->x, mouse->y), 0);
				mouse->shape.ComputeAABB(&m, mt, 0);
				if (!b2TestOverlap(m, triggerAABB))
				{
					b2RayCastInput input;
					input.p1 = b2Vec2(mouse->x, mouse->y);
					input.p2 = b2Vec2(triggers[i]->x, triggers[i]->y);
					input.maxFraction = .5f;

					b2RayCastOutput output;
					bool hit = triggers[i]->shape.RayCast(&output, input, triggerTransform, 0);
					if (hit)
					{
						b2Vec2 hitPoint = input.p1 + output.fraction * (input.p2 - input.p1);
						mouse->x = hitPoint.x;
						mouse->y = hitPoint.y;
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
