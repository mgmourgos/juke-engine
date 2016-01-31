#pragma once
#include "Command.h"
#include <typeinfo>

class GameActor;

class PlayerState 
{

public:
	virtual void handleCommand(GameActor& game_actor, Command& command) = 0;
	virtual void update(GameActor& game_actor, const int elapsed_time_ms) = 0;
};