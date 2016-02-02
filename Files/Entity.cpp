#include "Entity.h"
#include "Physics.h"

Entity::Entity() : x_vel(0), y_vel(0), x_acc(0), y_acc(0), width(0), height(0)
{
	std::cout << "set Gravity in entity class constructor1		Base Class" << std::endl;

}

Entity::Entity(int x_, int y_) : x_vel(0), y_vel(0), x_acc(0), y_acc(0), width(0), height(0)
{
	std::cout << "set Gravity in player class constructor2		Base Class" << std::endl;

}

Box Entity::getBox() const{
	Box box(x_pos, y_pos, width, height, x_vel, y_vel, x_acc, y_acc);
	return box;
}

void Entity::setBox(Box b1) {
	x_pos = b1.x;
	y_pos = b1.y;
	x_vel = b1.vx;
	y_vel = b1.vy;
	x_acc = b1.ax;
	y_acc = b1.ay;
}

void Entity::addCollision(std::unique_ptr<CollisionData> p)
{
	collision_vector.push_back(std::move(p));
}

void Entity::doPhysics(int elapsed_time_ms, double max_velocity) {

	Box final_box = Physics::actPhysicsOn(elapsed_time_ms, max_velocity, getBox());

	setBox(final_box);
}


Entity::~Entity()
{
}
