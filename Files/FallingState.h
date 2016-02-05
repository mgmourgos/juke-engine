#pragma once
#include "MoveContextState.h"
#include "MoveCommand.h"

class FallingState : public MoveContextState
{
public:
	FallingState();
	~FallingState();

	void handleCommand(GameActor& game_actor, const Command& command) override;
	void update(GameActor& game_actor, const int elapsed_time_ms) override;

	//Overloaded functions from MoveContextState
	void moveLeft(GameActor& game_actor) override;
	void moveRight(GameActor& game_actor) override;
};

