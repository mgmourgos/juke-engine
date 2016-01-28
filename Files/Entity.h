#pragma once
#include "Graphics.h"
#include "Box.h"
class Entity
{//Includes anything rendered or updated during a frame

protected:
	double total_vel;
	double x_pos, y_pos;
	double x_vel, y_vel;
	double x_acc, y_acc;
	int width, height;
public:
	virtual void update(int elapsed_time_ms) = 0;
	virtual void draw(Graphics& graphics) = 0;
	Box getBox(); 

	Entity();
	Entity(int x_, int y_);
	~Entity();
};

