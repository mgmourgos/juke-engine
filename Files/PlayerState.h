#pragma once
#include "Command.h"

class Actor;

class PlayerState
{
public:
	virtual ~PlayerState() {}
	virtual void handleCommand(Actor& actor, const Command& command) = 0;
	virtual void update(Actor& actor, const int elapsed_time_ms) = 0;

	virtual void onEntry(Actor& actor) {}
	virtual void onExit(Actor& actor) {}

};