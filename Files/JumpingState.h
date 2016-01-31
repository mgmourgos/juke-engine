#pragma once
#include "PlayerState.h"
#include "MoveCommand.h"
#include "FallingState.h"
//#include "OnGroundState.h"


class JumpingState : public PlayerState
{
public:
	JumpingState();
	~JumpingState();

	void handleCommand(GameActor& game_actor, Command& command);
	void update(GameActor& game_actor, const int elapsed_time_ms);
};

