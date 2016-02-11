#pragma once
#include "MoveContextState.h"
#include "MoveCommand.h"

class FallingState : public MoveContextState
{
public:
	FallingState();
	~FallingState();

	void handleCommand(Actor& actor, const Command& command) override;
	void update(Actor& actor, const int elapsed_time_ms) override;

	//Overloaded functions from MoveContextState
	void moveLeft(Actor& actor) override;
	void moveRight(Actor& actor) override;
};

