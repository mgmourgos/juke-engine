#pragma once
#include "Command.h"

class GameActor;

class PlayerState 
{
public:
	virtual ~PlayerState() {}
	virtual void handleCommand(GameActor& game_actor, const Command& command) = 0;
	virtual void update(GameActor& game_actor, const int elapsed_time_ms) = 0;
};