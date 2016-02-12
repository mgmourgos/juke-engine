#pragma once
#include "Box.h"
#include "CollisionData.h"
#include <memory>
#include <vector>

class Physics
{

	struct CollisionNormals
	{
		bool top;
		bool bottom;
		bool left;
		bool right;
		CollisionNormals() : top(false), bottom(false), left(false), right(false) {}
		void reset() { top = bottom = left = right = false; }
	};

	CollisionNormals collision_normals;

	void setCollisionNormal(CollisionNormal normal);

public:
	Box handleCollisions(std::vector<std::shared_ptr<CollisionData>> collision_data, double& remaining_time_ms, Box entity_box);
	Box actPhysicsOn(double elapsed_time_ms, double maxVelocity, Box box);
	Box update(std::vector<std::shared_ptr<CollisionData>> collision_data, Box entity_box, float max_velocity, int elapsed_time_ms);
};

