#pragma once
#include "PlayerState.h"
#include "MoveCommand.h"

class FallingState :
	public PlayerState
{
public:
	FallingState();
	~FallingState();

	void handleCommand(GameActor& game_actor, Command& command);
	void update(GameActor& game_actor, const int elapsed_time_ms);
};

