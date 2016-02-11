#pragma once
#include "Graphics.h"
#include "Box.h"
#include "CollisionData.h"
#include <vector>



class Entity
{//Includes anything rendered or updated during a frame
	friend class OnGroundState;
	friend class JumpingState;
	friend class FallingState;
	friend class MoveContextState;
	friend class PushingState;
	friend class Camera;

protected:

	double x_pos, y_pos;
	int width, height;

	CollisionType collision_type;

	std::vector <std::shared_ptr<CollisionData>> collision_vector;

	struct CollisionNormals
	{
		bool top;
		bool bottom;
		bool left;
		bool right;
		CollisionNormals() : top(false), bottom(false), left(false), right(false) {}
		void reset() { top = bottom = left = right = false; }
	};

	CollisionNormals collision_normals;

public:
	virtual void update(int elapsed_time_ms) = 0;
	virtual void draw(const Graphics& graphics, int x_render_pos, int y_render_pos) const = 0;

	virtual Box getBox() const = 0;
	virtual void setBox(Box b1) = 0;

	CollisionType getCollisionType() const { return collision_type; };
	void addCollision(std::shared_ptr<CollisionData>);

	void setCollisionNormal(CollisionNormal normal);
	void setCollisionType(CollisionType type);

	Entity(int x_, int y_, int width_, int height_, CollisionType col_type_);
	virtual ~Entity();
};

