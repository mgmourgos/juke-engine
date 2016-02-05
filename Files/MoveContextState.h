#pragma once
#include "PlayerState.h"
//#include "Player.h"
//#include "GameActor.h"
class MoveContextState :
	public PlayerState
{
public:
	virtual void handleCommand(GameActor& game_actor, const Command& command) = 0;
	virtual void update(GameActor& game_actor, const int elapsed_time_ms) = 0;
	
	virtual void moveLeft(GameActor& game_actor);
	virtual void moveRight(GameActor& game_actor);
	virtual void jump(GameActor& game_actor);
};

