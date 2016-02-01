#pragma once
#include "MoveContextState.h"
#include "MoveCommand.h"
#include <algorithm>
#include "JumpingState.h"

class OnGroundState : public MoveContextState
{

public:
	OnGroundState();
	~OnGroundState();

	void handleCommand(GameActor& game_actor, Command& command) override;
	void update(GameActor& game_actor, const int elapsed_time_ms) override;
};

