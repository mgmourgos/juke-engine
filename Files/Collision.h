#pragma once
#include "Box.h"
#include "CollisionData.h"
#include "Entity.h"

class Collision
{
public:
	bool isCollisionPossible(Box b1, Box b2, int elapsed_time_ms);
	Box getBroadphaseBox(Box b1, int elapsedTime);
	std::unique_ptr<CollisionData> getCollisionData(const Entity &e1, const Entity &e2, int elapsed_time_ms);
	Collision();
	~Collision();
};

