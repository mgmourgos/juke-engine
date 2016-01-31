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

void Entity::doPhysics(int elapsed_time_ms) {
	
	x_pos += x_vel * elapsed_time_ms;
	y_pos += y_vel * elapsed_time_ms;

	x_vel += x_acc * elapsed_time_ms;
	y_vel += y_acc * elapsed_time_ms;

}

Entity::~Entity()
{
}
