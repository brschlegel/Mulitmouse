#include "ShapeManager.h"

void ShapeManager::HandleCollision(ShapeStorage* shapes)
{
	for (int i = 0; i < shapes->count(); i++)
	{
		b2AABB a;
		b2Transform at;
		at.Set(b2Vec2(shapes->shapes[i]->x, shapes->shapes[i]->y), 0);
		shapes->shapes[i]->shape.ComputeAABB(&a, at, 0);
		//Other shapes
		for (int j = 0; j < shapes->count(); j++)
		{
			if (i == j)
				continue;

			
			if ((shapes->shapes[i]->mask & (int)shapes->shapes[j]->layer) > 0)
			{
				b2AABB b;
				b2Transform bt;
				bt.Set(b2Vec2(shapes->shapes[j]->x, shapes->shapes[j]->y), 0);
				shapes->shapes[j]->shape.ComputeAABB(&b, bt, 0);

				if (b2TestOverlap(a, b))
				{
					shapes->shapes[i]->onCollision(shapes->shapes[j]);
				}
			}
		}
		//mice handled seperately
		for (int j = 0; j < MouseManager::getInstance()->mice.size(); j++)
		{

			if ((shapes->shapes[i]->mask & (int)MouseManager::getInstance()->mice[j]->layer) >0)
			{
				b2AABB b;
				b2Transform bt;
				bt.Set(b2Vec2(MouseManager::getInstance()->mice[j]->x, MouseManager::getInstance()->mice[j]->y), 0);
				MouseManager::getInstance()->mice[j]->shape.ComputeAABB(&b, bt, 0);
				if (b2TestOverlap(a, b))
				{
					shapes->shapes[i]->onCollision(MouseManager::getInstance()->mice[j]);
				}
			}
		}

		//Line time
		for (int j = 0; j < shapes->lines.size(); j++)
		{
			if (((shapes->lines[j]->mask & (int)shapes->shapes[i]->layer) > 0))
			{
				for (int k = 0; k < shapes->lines[j]->LOD; k++)
				{
					if (shapes->shapes[i]->shape.TestPoint(at, shapes->lines[j]->points[k].position) && shapes->lines[j]->points[k].active)
					{
						shapes->lines[j]->onCollision(shapes->shapes[i], k);
					}
				}
			}
		}
	}
	//Collect events and delete objects
	for (int i = EventStorage::getInstance()->collisionEvents.size() - 1; i > -1 ; i--)
	{
		shapes->deleteObject(EventStorage::getInstance()->pollCollisionEvent(i));
	}
}

void ShapeManager::update(ShapeStorage* storage)
{
	storage->world->Step(1.0f / 60.0f, 6, 2);
	for (int i = 0; i < storage->count(); i++)
	{
		storage->shapes[i]->updateObj();
	
	}
	//Keep x and y updated on physics objects
	vector<PolygonPhysicsObject*> bodies = storage->getObjectOfType<PolygonPhysicsObject>();
	for (int i = 0; i < bodies.size(); i++)
	{
		b2Transform transform = bodies[i]->body->GetTransform();
		bodies[i]->x = transform.p.x;
		bodies[i]->y = transform.p.y;
	}
	HandleCollision(storage);
}

void ShapeManager::draw(ShapeStorage* storage)
{
	for (int i = 0; i < storage->count(); i++)
	{
		storage->shapes[i]->draw();
	}
}
