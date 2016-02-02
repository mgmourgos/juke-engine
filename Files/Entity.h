#pragma once
#include "Graphics.h"
#include "Box.h"
#include <algorithm>
//#include "Collision.h"
#include "CollisionData.h"
#include <vector>

class Entity
{//Includes anything rendered or updated during a frame
	friend class OnGroundState;
	friend class JumpingState;
	friend class FallingState;
	friend class MoveContextState;
protected:
	double x_pos, y_pos;
	double x_vel, y_vel;
	double x_acc, y_acc;
	int width, height;
	CollisionType type;
	std::vector <std::unique_ptr<CollisionData>> collision_vector;
public:
	virtual void update(int elapsed_time_ms) = 0;
	virtual void draw(Graphics& graphics) = 0;
	CollisionType getCollisionType() const { return type; };
	void addCollision(std::unique_ptr<CollisionData>);
	Box getBox() const;
	void setBox(Box b1);
	void doPhysics(int elapsed_time_ms, double max_velocity);

	Entity();
	Entity(int x_, int y_);
	virtual ~Entity();
};

