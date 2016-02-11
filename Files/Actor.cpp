#include "Actor.h"
#include "PlayerConstants.h"

int Actor::id_counter = 0;

Actor::Actor(int x_, int y_, int width_, int height_, CollisionType col_type) : Entity(x_, y_, width_, height_, col_type),
x_vel(0), y_vel(0), x_acc(0), y_acc(gravity)
{
	id = id_counter++;
}

Actor::~Actor() {

}

void Actor::handleCollision(CollisionData& collision_data, double& remaining_time_ms, int elapsed_time_ms)
{

	double offset_collision_time = collision_data.collision_time - .000000001;//offsets the position to right before the collision

	if (collision_data.normal == BOTTOM || collision_data.normal == TOP)
	{
		y_pos += offset_collision_time * y_vel;

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
			x_pos += offset_collision_time * x_vel;
		}
		
		remaining_time_ms -= offset_collision_time;
	}
	else if (collision_data.normal == RIGHT || collision_data.normal == LEFT)
	{
		//Moving platforms will not work
		x_pos += offset_collision_time * x_vel;

		//can't move in y if colliding with obj in y velocity direction
		if (!(collision_normals.bottom && y_vel < 0) && !(collision_normals.top && y_vel > 0))  //clear this up
		{
			y_pos += offset_collision_time * y_vel;
		}
		x_vel = 0;
		remaining_time_ms -= offset_collision_time;
	}
}

Box Actor::getBox() const {
	Box box(x_pos, y_pos, width, height, x_vel, y_vel, x_acc, y_acc);
	return box;
}

void Actor::setBox(Box b1)
{
	x_pos = b1.x;
	y_pos = b1.y;
	x_vel = b1.vx;
	y_vel = b1.vy;
	x_acc = b1.ax;
	y_acc = b1.ay;
}