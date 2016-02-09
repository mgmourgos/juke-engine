#pragma once
#include "MoveContextState.h"

class PushingState : public MoveContextState
{
	bool pushing;

public:
	PushingState();
	~PushingState();

	void handleCommand(GameActor& game_actor, const Command& command) override;
	void update(GameActor& game_actor, const int elapsed_time_ms) override;

	void moveRight(GameActor& game_actor) override;
	void moveLeft(GameActor& game_actor) override;
};

