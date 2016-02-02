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
	MOVABLE,
	UNMOVABLE
	
};

class CollisionData
{
	friend class Player;
	friend class GameActor;

	//double x_pos, y_pos;//Top left coords of obj when collision took place
	double x_vel_obj, y_vel_obj;//The velocity of the object being collided with
	int collision_time;//The time of the collision
	CollisionNormal normal;//The side the obj was collided on
	CollisionType type;//The type of object being collided with
public:
	CollisionData();
	CollisionData(double x_vel_obj_, double y_vel_obj_, int collision_time_, CollisionNormal normal_, CollisionType type_) :
		x_vel_obj(x_vel_obj_), y_vel_obj(y_vel_obj_), collision_time(collision_time_), normal(normal_), type(type_) {}
	~CollisionData();
};

