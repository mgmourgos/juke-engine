#pragma once
#include "Entity.h"
#include <memory>

class PlayerState;
class Command;

class GameActor : public Entity
{
	friend class OnGroundState;
	friend class JumpingState;
	friend class FallingState;

protected:
	static int id_counter;
	int id;

	//Temporary
	bool jumping;

public:
	GameActor();
	~GameActor();

	int getId() { return id; }
	virtual void moveLeft() = 0;
	virtual void moveRight() = 0;
	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
	virtual void jump() = 0;
	virtual void handleCommand(Command& command) = 0;

	virtual void setState(PlayerState* new_state) = 0;
};