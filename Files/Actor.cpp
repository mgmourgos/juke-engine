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