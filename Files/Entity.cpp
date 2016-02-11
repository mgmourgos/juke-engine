#include "Entity.h"
#include "Physics.h"

Entity::Entity(int x_, int y_, int width_, int height_, CollisionType col_type) : 
x_pos(x_), y_pos(y_), width(width_), height(height_),
collision_type(col_type)
{
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

void Entity::addCollision(std::shared_ptr<CollisionData> p)
{
	collision_vector.push_back(move(p));
}

void Entity::setCollisionType(CollisionType type)
{
	collision_type = type;
}

Entity::~Entity()
{
}
