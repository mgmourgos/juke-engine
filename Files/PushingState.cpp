#include "PushingState.h"
#include "PlayerConstants.h"
#include "MoveCommand.h"
#include "FallingState.h"
#include "OnGroundState.h"
#include "Actor.h"
#include "CollisionData.h"


PushingState::PushingState() : MoveContextState(PUSH_MAX_VELOCITY), pushing(true)
{
}

PushingState::~PushingState()
{
}

void PushingState::handleCommand(Actor& actor, const Command& command)
{
	switch (command.getName())
	{
	case MOVE_LEFT:
		moveLeft(actor);
		break;
	case MOVE_RIGHT:
		moveRight(actor);
		break;
	case PUSH:
		pushing = true;
		break;
	default:
		break;
	};
}

void PushingState::update(Actor& actor, const int elapsed_time_ms)
{
	//We have a major issue here and in our other states
	//When we call setMoveContextState, we are deleting the state we are in. 
	//This can lead to memory errors as we are still in the state that was just deleted.
	//this seems to be fixed by adding return after call to setMoveContextState
	//Not sure if this is a good solution though.
	
	if (actor.collision_normals.bottom == false)
	{
		actor.setMoveContextState(new FallingState());
		return;
	}

	if(pushing == false)
	{
		actor.setMoveContextState(new OnGroundState());
	}
	else 
	{
		if (fabs(actor.x_vel) <= .0001) {
			actor.x_vel = 0;
		}

		if (actor.x_acc == 0) {
			actor.x_vel *= slowDownFactor;
		}

		pushing = false;
	}
}

void PushingState::moveRight(Actor& actor)
{
	if (actor.x_acc <= 0) 
	{
		actor.x_acc += pushAcceleration;
	}
}

void PushingState::moveLeft(Actor& actor)
{
	//handles moving left and right
	if (actor.x_acc >= 0)
	{
		actor.x_acc += -pushAcceleration;
	}
}

void PushingState::onEntry(Actor& actor)
{
	actor.setCollisionType(PUSHING);
}

void PushingState::onExit(Actor& actor)
{
	actor.setCollisionType(MOVEABLE);
}