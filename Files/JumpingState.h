#pragma once
#include "MoveContextState.h"
#include "MoveCommand.h"
#include "FallingState.h"

class JumpingState : public MoveContextState
{
public:
	JumpingState();
	~JumpingState();

	void handleCommand(GameActor& game_actor, Command& command) override;
	void update(GameActor& game_actor, const int elapsed_time_ms) override;

	//Overloaded functions from MoveContextState
	void moveLeft(GameActor& game_actor) override;
	void moveRight(GameActor& game_actor) override;
};

