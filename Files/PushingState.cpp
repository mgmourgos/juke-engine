#include "PushingState.h"
#include "PlayerConstants.h"
#include "MoveCommand.h"
#include "FallingState.h"
#include "OnGroundState.h"
#include "PushCommand.h"
#include "GameActor.h"



PushingState::PushingState() : pushing(true)
{
}


PushingState::~PushingState()
{
}

void PushingState::handleCommand(GameActor& game_actor, const Command& command)
{
	switch (command.getName())
	{
	case MOVE_LEFT:
		moveLeft(game_actor);
		break;
	case MOVE_RIGHT:
		moveRight(game_actor);
		break;
	case PUSH:
		pushing = true;
		break;
	default:
		break;
	};
}

void PushingState::update(GameActor& game_actor, const int elapsed_time_ms)
{
	//We have a major issue here and in our other states
	//When we call setMoveContextState, we are deleting the state we are in. 
	//This can lead to memory errors as we are still in the state that was just deleted.
	//this seems to be fixed by adding return after call to setMoveContextState
	//Not sure if this is a good solution though.

	
	if (game_actor.collision_normals.bottom == false)
	{
		game_actor.setMoveContextState(new FallingState());
		return;
	}

	if(pushing == false)
	{
		game_actor.setMoveContextState(new OnGroundState());
	}
	else 
	{
		pushing = false;
	}
}

void PushingState::moveRight(GameActor& game_actor)
{
	if (game_actor.x_acc <= 0) 
	{
		game_actor.x_acc += pushAcceleration;
	}
}

void PushingState::moveLeft(GameActor& game_actor)
{
	//handles moving left and right
	if (game_actor.x_acc >= 0)
	{
		game_actor.x_acc += -pushAcceleration;
	}
}
