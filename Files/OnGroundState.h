#pragma once
#include "MoveContextState.h"

class OnGroundState : public MoveContextState
{

public:
	OnGroundState();
	~OnGroundState();

	void handleCommand(Actor& actor, const Command& command) override;
	void update(Actor& actor, const int elapsed_time_ms) override;
	void push(Actor& actor) override;
};

