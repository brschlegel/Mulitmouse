#pragma once
#include "Level.h"

class PongListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact) {
        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData)
        {
            Box* b = static_cast<Box*>(bodyUserData);
            if (b->hasTag(Tag::Pong))
            {
                //if colliding to the left
                if (abs(contact->GetManifold()->localNormal.x) > 0)
                {
                    b2Vec2 prevVelocity = b->body->GetLinearVelocity();
                    b->body->SetLinearVelocity(b2Vec2(-prevVelocity.x, prevVelocity.y));
                }
                else if (abs(contact->GetManifold()->localNormal.y) > 0)
                {
                    b2Vec2 prevVelocity = b->body->GetLinearVelocity();
                    b->body->SetLinearVelocity(b2Vec2(prevVelocity.x, -prevVelocity.y));
                }
            }
        }

    }

};


class PongLevel :
    public Level
{
public:
    PongLevel();
    void update();
    PongListener listener;
    Goal* left;
    Goal* right;

};

