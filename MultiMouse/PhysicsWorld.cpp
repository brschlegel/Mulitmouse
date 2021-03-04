#include "PhysicsWorld.h"

void PhysicsWorld::Update()
{
    world->Step(1.0f / 60.0f, 6, 2);
}

PhysicsWorld::PhysicsWorld(b2Vec2 gravity)
{
    world = new b2World(gravity);
    std::cout << "bruh";
}

PhysicsWorld::PhysicsWorld()
{
    world = new b2World(b2Vec2(0, -9.8));
}

Box* PhysicsWorld::AddBox(float x, float y, float mass, Color color, float height, float width, float friction, float density, float angle, std::string name)
{
    Box* box = new Box(x, y, mass, color, height, width, friction, density, angle, name);
    box->body = world->CreateBody(&box->def);
    box->body->CreateFixture(&box->fixtureDef);
    box->body->SetUserData(box);
    bodies.push_back(box);
    return box;
}

Barrier* PhysicsWorld::AddRectBarrier(float x, float y, float width, float height, float angle, std::string name)
{
    Barrier* barrier = new Barrier(x, y, angle, name);
    barrier->setShapeAsBox(width, height);
    barrier->body = world->CreateBody(&barrier->def);
    barrier->body->CreateFixture(&barrier->shape, 0);
    barrier->body->SetUserData(barrier);
    bodies.push_back(barrier);
    return barrier;
}

void PhysicsWorld::draw()
{
    for (int i = 0; i < bodies.size(); i++)
    {
        bodies[i]->draw();
    }
}

void PhysicsWorld::deleteObject(int index)
{
    PolygonPhysicsObject* object = bodies[index];
    if (object->selected != nullptr)
    {
        object->selected->releasePhysicsSelect();
    }
    bodies.erase(bodies.begin() + index);
    world->DestroyBody(object->body);
    delete (object);
}

void PhysicsWorld::deleteObject(PolygonPhysicsObject* object)
{
    bodies.erase(std::find(bodies.begin(), bodies.end(), object));
    world->DestroyBody(object->body);
    delete(object);
}

PolygonPhysicsObject* PhysicsWorld::getBodyByName(std::string name)
{
    for (PolygonPhysicsObject* obj : bodies)
    {
        if (name == obj->name)
            return obj;
    }
    return nullptr;
}

std::vector<PolygonPhysicsObject*> PhysicsWorld::getBodyByTag(Tag tag)
{
    std::vector<PolygonPhysicsObject*> objs;
    for(PolygonPhysicsObject* obj : bodies)
    {
        if (obj->hasTag(tag))
        {
            objs.push_back(obj);
        }
    }
    return objs;
}


