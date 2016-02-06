#include "Entity.h"
#include "Physics.h"

Entity::Entity() : x_vel(0), y_vel(0), x_acc(0), y_acc(0), width(0), height(0)
{
}

Entity::Entity(int x_, int y_) : x_vel(0), y_vel(0), x_acc(0), y_acc(0), width(0), height(0)
{
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

void Entity::setCollisionNormal(CollisionNormal normal)
{
	switch(normal) {
		case TOP:
			collision_normals.top = true;
			break;
		case BOTTOM:
			collision_normals.bottom = true;
			break;
		case LEFT:
			collision_normals.left = true;
			break;
		case RIGHT:
			collision_normals.right = true;
			break;
	};
}

void Entity::addCollision(std::unique_ptr<CollisionData> p)
{
	collision_vector.push_back(std::move(p));
}

void Entity::doPhysics(double elapsed_time_ms, double max_velocity) {

	Box final_box = Physics::actPhysicsOn(elapsed_time_ms, max_velocity, getBox());

	setBox(final_box);
}


Entity::~Entity()
{
}
