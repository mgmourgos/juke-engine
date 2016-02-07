#include "GameActor.h"

int GameActor::id_counter = 0;

GameActor::GameActor() : jumping(true)
{
	id = id_counter++;
}

GameActor::~GameActor() {

}

void GameActor::handleCollision(CollisionData& collision_data, double& remaining_time_ms, int elapsed_time_ms)
{
	collision_data.collision_time -= .000000001;//offsets the position to right before the collision
	if (collision_data.normal == BOTTOM || collision_data.normal == TOP)
	{
		y_pos += collision_data.collision_time * y_vel;

		//y_vel matches that of object if player is on top of rising platform, or
		//player is below falling platform
		if (collision_data.normal == BOTTOM && collision_data.y_vel_obj > 0 ||
			collision_data.normal == TOP && collision_data.y_vel_obj < 0) {  
			
			y_vel = collision_data.y_vel_obj;
		} else
		{
			y_vel = 0;
		}
		
		//can't move in x if colliding with obj in x velocity direction
		if ( !(collision_normals.left && x_vel < 0) && !(collision_normals.right && x_vel > 0) )
		{
			x_pos += collision_data.collision_time * x_vel;
		}
		
		remaining_time_ms -= collision_data.collision_time;
	}
	else if (collision_data.normal == RIGHT || collision_data.normal == LEFT)
	{
		//Moving platforms will not work
		x_pos += collision_data.collision_time * x_vel;

		//can't move in y if colliding with obj in y velocity direction

		if (!(collision_normals.bottom && y_vel < 0) && !(collision_normals.top && y_vel > 0))  //clear this up
		{
			y_pos += collision_data.collision_time * y_vel;
		}
		x_vel = 0;
		remaining_time_ms -= collision_data.collision_time;
	}


}