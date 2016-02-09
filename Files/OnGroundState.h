#pragma once
#include "MoveContextState.h"

class OnGroundState : public MoveContextState
{

public:
	OnGroundState();
	~OnGroundState();

	void handleCommand(GameActor& game_actor, const Command& command) override;
	void update(GameActor& game_actor, const int elapsed_time_ms) override;
	void push(GameActor& game_actor) override;
};

