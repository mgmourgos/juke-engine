#include "GameActor.h"

int GameActor::id_counter = 0;

GameActor::GameActor() : jumping(true)
{
	id = id_counter++;
}

GameActor::~GameActor() {

}

void GameActor::handleCollision(CollisionData& collision_data, int& remaining_time_ms, int elapsed_time_ms)
{
	if (collision_data.normal == BOTTOM)
	{
		y_pos += collision_data.collision_time * y_vel;
		x_pos += collision_data.collision_time * x_vel;
		y_vel = 0;
		remaining_time_ms -= collision_data.collision_time;
	}
	else if (collision_data.normal == TOP) {
		y_pos += collision_data.collision_time * y_vel;
		x_pos += collision_data.collision_time * x_vel;
		y_vel = 0;
		remaining_time_ms -= collision_data.collision_time;
	}
	else if (collision_data.normal == RIGHT || collision_data.normal == LEFT)
	{
		//Moving platforms will not work
		x_pos += collision_data.collision_time * x_vel;
		y_pos += collision_data.collision_time * y_vel;
		x_vel = 0;
		remaining_time_ms -= collision_data.collision_time;
	}


}