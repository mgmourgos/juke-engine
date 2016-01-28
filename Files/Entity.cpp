#include "Entity.h"


Entity::Entity() : x_vel(0), y_vel(0), x_acc(0), y_acc(0), total_vel(0)
{
}

Entity::Entity(int x_, int y_) : x_vel(0), y_vel(0), x_acc(0), y_acc(0), total_vel(0)
{
}

Box Entity::getBox() {
	Box box(x_pos, y_pos, width, height, x_vel, y_vel);
	return box;
}
Entity::~Entity()
{
}
