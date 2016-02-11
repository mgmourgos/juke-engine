#include "FallingState.h"
#include "PlayerConstants.h"
#include "OnGroundState.h"
#include "Actor.h"

FallingState::FallingState()
{
}


FallingState::~FallingState()
{
}

void FallingState::handleCommand(Actor& game_actor, const Command& command) {

	switch (command.getName())
	{
	case MOVE_LEFT:
		moveLeft(game_actor);
		break;
	case MOVE_RIGHT:
		moveRight(game_actor);
		break;
	default:
		break;
	};
}

void FallingState::update(Actor& actor, const int elapsed_time_ms) {

	if (actor.collision_normals.bottom == true)
	{
		actor.setMoveContextState(new OnGroundState());
	}
}

void FallingState::moveLeft(Actor& actor) {
	if (actor.x_acc >= 0){
		actor.x_acc += -moveAcceleration * inAirSlowdownFactor;
	}
}

void FallingState::moveRight(Actor& actor) {
	if (actor.x_acc <= 0) {
		actor.x_acc += moveAcceleration * inAirSlowdownFactor;
	}
}
