#include "Physics.h"
#include <algorithm>

Box Physics::update(std::vector<std::shared_ptr<CollisionData>> collision_data, Box entity_box, float max_velocity, int elapsed_time_ms)
{
	double remaining_time_ms = static_cast<double>(elapsed_time_ms);

	entity_box = handleCollisions(collision_data, remaining_time_ms, entity_box);

	entity_box = actPhysicsOn(remaining_time_ms, max_velocity, entity_box);

	return entity_box;
}

Box Physics::actPhysicsOn(double elapsed_time_ms, double max_velocity, Box box) {

	//Position and Velocity setting
	//box.x += (0.5f) * box.ax * elapsed_time_ms * elapsed_time_ms + box.vx * elapsed_time_ms;
	//box.y += (0.5f) * box.ay * elapsed_time_ms * elapsed_time_ms + box.vy * elapsed_time_ms;

	box.x += box.vx * elapsed_time_ms;
	box.y += box.vy * elapsed_time_ms;

	box.vx += box.ax * elapsed_time_ms;
	box.vy += box.ay * elapsed_time_ms;

	//Terminal Velocity Check
	if (box.ax < 0.0f) {
		box.vx = std::max(box.vx, -max_velocity);
	}
	else if (box.ax > 0.0f) {
		box.vx = std::min(box.vx, max_velocity);
	}

	return box;
}

Box Physics::handleCollisions(std::vector<std::shared_ptr<CollisionData>> collision_vector, double& remaining_time_ms, Box entity_box)
{
	Box collision_box;

	for (auto& collision : collision_vector)
	{
		setCollisionNormal(collision->normal);
	}

	for (auto& collision_data : collision_vector)
	{

		double offset_collision_time = collision_data->collision_time - .000000001;//offsets the position to right before the collision

		if (collision_data->normal == BOTTOM || collision_data->normal == TOP)
		{
			entity_box.y += offset_collision_time * entity_box.vy;

			//y_vel matches that of object if player is on top of rising platform, or
			//player is below falling platform
			if (collision_data->normal == BOTTOM && collision_data->y_vel_obj > 0 ||
				collision_data->normal == TOP && collision_data->y_vel_obj < 0) {

				entity_box.vy = collision_data->y_vel_obj;
			}
			else
			{
				entity_box.vy = 0;
			}

			//can't move in x if colliding with obj in x velocity direction
			if (!(collision_normals.left && entity_box.vx < 0) && !(collision_normals.right && entity_box.vx > 0))
			{
				entity_box.x += offset_collision_time * entity_box.vx;
			}

			remaining_time_ms -= offset_collision_time;
		}
		else if (collision_data->normal == RIGHT || collision_data->normal == LEFT)
		{
			//Moving platforms will not work
			entity_box.x += offset_collision_time * entity_box.vx;

			//can't move in y if colliding with obj in y velocity direction
			if (!(collision_normals.bottom && entity_box.vy < 0) && !(collision_normals.top && entity_box.vy > 0))  //clear this up
			{
				entity_box.y += offset_collision_time * entity_box.vy;
			}
			entity_box.vx = 0;
			remaining_time_ms -= offset_collision_time;
		}
	}

	return entity_box;
}

void Physics::setCollisionNormal(CollisionNormal normal)
{
	switch (normal) {
	case TOP:
		collision_normals.top = true;
		break;
	case BOTTOM:
		collision_normals.bottom = true;
		break;
	case LEFT:
		collision_normals.left = true;
		break;
	case RIGHT:
		collision_normals.right = true;
		break;
	};
}
