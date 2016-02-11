#pragma once
enum CollisionNormal
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

enum CollisionType
{
	MOVEABLE,       //moveable without being pushed
	UNMOVEABLE,		//doesn't move
	PUSHING,
	PUSHABLE
};

class CollisionData
{

public:

	const double x_vel_obj, y_vel_obj;//The velocity of the object being collided with
	const double collision_time;//The time of the collision

	const CollisionNormal normal;//The side the obj was collided on
	const CollisionType type;//The type of object being collided with

	CollisionData(double x_vel_obj_, double y_vel_obj_, double collision_time_, CollisionNormal normal_, CollisionType type_) :
		x_vel_obj(x_vel_obj_), y_vel_obj(y_vel_obj_), collision_time(collision_time_), normal(normal_), type(type_) {}
	~CollisionData();
};

