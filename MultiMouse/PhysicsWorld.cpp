#include "PhysicsWorld.h"

void PhysicsWorld::Update()
{
    world->Step(1.0f / 60.0f, 6, 2);
}

PhysicsWorld::PhysicsWorld(b2Vec2 gravity)
{
    world = new b2World(gravity);

}

Box* PhysicsWorld::AddBox(float x, float y, float mass, Color color, float height, float width, float friction, float density, float angle)
{
    Box* box = new Box(x, y, mass, color, height, width, friction, density, angle);
    box->body = world->CreateBody(&box->def);
    box->body->CreateFixture(&box->fixtureDef);
    bodies.push_back(box);
    return box;
}

Barrier* PhysicsWorld::AddRectBarrier(float x, float y, float width, float height, float angle)
{
    Barrier* barrier = new Barrier(x, y, angle);
    barrier->setShapeAsBox(width, height);
    barrier->body = world->CreateBody(&barrier->def);
    barrier->body->CreateFixture(&barrier->shape, 0);
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


