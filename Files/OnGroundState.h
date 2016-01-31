#pragma once
#include "PlayerState.h"
#include "MoveCommand.h"
#include <algorithm>
#include "JumpingState.h"

class OnGroundState : public PlayerState
{

public:
	OnGroundState();
	~OnGroundState();

	void handleCommand(GameActor& game_actor, Command& command);
	void update(GameActor& game_actor, const int elapsed_time_ms);
};

