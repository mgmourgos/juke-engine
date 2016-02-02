#pragma once
#include "Box.h"
#include "CollisionData.h"
#include "Entity.h"

class Collision
{
public:

	static bool isCollisionPossible(Box b1, Box b2, int elapsed_time_ms);
	static std::unique_ptr<CollisionData> getCollisionData(const Entity& e1, const Entity& e2, int elapsed_time_ms);

	static std::unique_ptr<CollisionData> determineCollisionData(CollisionNormal normal, Box b1, Box b2, CollisionType entity_2_collision_type, int elapsed_time_ms);

	static Box getBroadphaseBox(Box b1, int elapsedTime);
	static bool doesXAxisCollide(Box b1, Box b2);
	static bool doesYAxisCollide(Box b1, Box b2);

	Collision();
	~Collision();
};

