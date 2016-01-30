#include "Entity.h"


Entity::Entity() : x_vel(0), y_vel(0), x_acc(0), y_acc(0), total_vel(0), toUpdate(true)
{
}

Entity::Entity(int x_, int y_) : x_vel(0), y_vel(0), x_acc(0), y_acc(0), total_vel(0), toUpdate(true)
{
}

Box Entity::getBox() {
	Box box(x_pos, y_pos, width, height, x_vel, y_vel);
	return box;
}

void Entity::setBox(Box b1) {
	x_pos = b1.x;
	y_pos = b1.y;
	x_vel = b1.vx;
	y_vel = b1.vy;
}

void Entity::setToUpdate(bool toUpdate_) {
	toUpdate = toUpdate_;
}

Entity::~Entity()
{
}
