#pragma once
enum CollisionNormal
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

class CollisionData
{
	double x_pos, y_pos;//Top left coords of obj when collision took place
	int collision_time;
	CollisionNormal normal;
public:
	CollisionData(double x_pos_, double y_pos_, int collision_time_, CollisionNormal normal_) :
		x_pos(x_pos_), y_pos(y_pos_), collision_time(collision_time_), normal(normal_) {}
	~CollisionData();
};

