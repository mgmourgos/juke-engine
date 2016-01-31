#pragma once
#include "Graphics.h"
#include "Box.h"
class Entity
{//Includes anything rendered or updated during a frame
	friend class OnGroundState;
	friend class JumpingState;
	friend class FallingState;
protected:
	double total_vel;
	double x_pos, y_pos;
	double x_vel, y_vel;
	double x_acc, y_acc;
	int width, height;
	bool toUpdate;
public:
	virtual void update(int elapsed_time_ms) = 0;
	virtual void draw(Graphics& graphics) = 0;
	Box getBox();
	void setBox(Box b1);
	void setToUpdate(bool);
	void doPhysics(int elapsed_time_ms);

	Entity();
	Entity(int x_, int y_);
	~Entity();
};

