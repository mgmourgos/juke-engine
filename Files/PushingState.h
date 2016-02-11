#pragma once
#include "MoveContextState.h"

class PushingState : public MoveContextState
{
	bool pushing;

public:
	PushingState();
	~PushingState();

	void handleCommand(Actor& actor, const Command& command) override;
	void update(Actor& actor, const int elapsed_time_ms) override;

	void moveRight(Actor& actor) override;
	void moveLeft(Actor& actor) override;

	void onEntry(Actor& actor) override;
	void onExit(Actor& actor) override;
};

