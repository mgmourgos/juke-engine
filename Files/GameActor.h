#pragma once
class GameActor
{

protected:

	double x_pos, y_pos;
	double x_vel, y_vel;
	double x_acc, y_acc;
	double total_vel;

public:
	GameActor();
	~GameActor();

	virtual void moveLeft() = 0;
	virtual void moveRight() = 0;
	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
};

