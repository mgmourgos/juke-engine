#pragma once
#include "Entity.h"
#include <memory>

class PlayerState;
class Command;

class GameActor : public Entity
{
	//Might not need these friends in game_actor...
	friend class OnGroundState;
	friend class JumpingState;
	friend class FallingState;
	friend class MoveContextState;

protected:
	static int id_counter;
	int id;

	//Temporary
	bool jumping;

public:
	GameActor();
	virtual ~GameActor();

	int getId() { return id; }
	virtual void moveLeft() = 0;
	virtual void moveRight() = 0;
	virtual void jump() = 0;
	virtual void handleCommand(Command& command) = 0;

	virtual void setMoveContextState(MoveContextState* new_state) = 0;
};