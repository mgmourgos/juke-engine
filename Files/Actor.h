#pragma once
#include "Entity.h"

class PlayerState;
class Command;
class CollisionData;

//Entity that can recieve commands
class Actor : public Entity
{
	//Might not need these friends in game_actor...
	friend class OnGroundState;
	friend class JumpingState;
	friend class FallingState;
	friend class MoveContextState;
	friend class PushingState;

protected:

	double x_vel, y_vel;
	double x_acc, y_acc;

	static int id_counter;
	int id;

public:
	Actor(int x_, int y_, int width_, int height_, CollisionType col_type);
	virtual ~Actor();

	int getId() const { return id; }

	Box getBox() const override;
	void setBox(Box b1) override;

	virtual void handleCommand(const Command& command) = 0;

	virtual void setMoveContextState(MoveContextState* new_state) = 0;
};