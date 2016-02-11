#pragma once
#include "Box.h"
#include "CollisionData.h"
#include <memory>
#include <vector>

class Physics
{

public:
	Box handleCollisions(std::vector<std::shared_ptr<CollisionData>> collision_data, int elapsed_time_ms);
	Box actPhysicsOn(double elapsed_time_ms, double maxVelocity, Box box);
};

