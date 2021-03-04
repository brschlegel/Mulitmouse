#include "KinematicCollisionFunctions.h"

int PongCollisions(PolygonPhysicsObject* a, b2AABB b)
{
	//Man I am not proud of this code. Its making ghost colliders to check where the collision is coming from. May God have mercy on my soul
	Box* ab = dynamic_cast<Box*>(a);
	if (ab != nullptr)
	{
		float offset = .1;

		b2Transform at = ab->body->GetTransform();
		//checking from the side
		PolygonObject apw = PolygonObject(ab->body->GetPosition().x, ab->body->GetPosition().y, Color::getBlue(), 0);
		apw.setShapeAsBox(ab->width + offset, ab->height);
		b2AABB apAABB;
		apw.shape.ComputeAABB(&apAABB, at, 0);

		if (b2TestOverlap(apAABB, b))
		{
			b2Vec2 prevVel = b2Vec2(ab->body->GetLinearVelocity());
			std::cout << "from the side!" << std::endl;
			ab->body->SetLinearVelocity(b2Vec2(-prevVel.x, prevVel.y));
		}

		PolygonObject aph =  PolygonObject(ab->body->GetPosition().x, ab->body->GetPosition().y, Color::getBlue(), 0);
		aph.setShapeAsBox(ab->width, ab->height + offset);
		b2AABB aphAABB;
		aph.shape.ComputeAABB(&aphAABB, at, 0);
		if (b2TestOverlap(aphAABB, b)) 
		{
			b2Vec2 prevVel = b2Vec2(ab->body->GetLinearVelocity());
			ab->body->SetLinearVelocity(b2Vec2(prevVel.x, -prevVel.y));
			std::cout << "from the top!" << std::endl;
		}
	}

	

	
	return 0;
}
