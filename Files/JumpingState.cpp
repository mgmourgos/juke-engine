#include "JumpingState.h"
#include "PlayerConstants.h"
#include "OnGroundState.h"
#include "FallingState.h"
#include "Actor.h"

JumpingState::JumpingState()
{
}


JumpingState::~JumpingState()
{
}

void JumpingState::handleCommand(Actor& actor, const Command& command) {

	switch (command.getName())
	{
	case MOVE_LEFT:
		moveLeft(actor);
		break;
	case MOVE_RIGHT:
		moveRight(actor);
		break;
	default:
		break;
	};
}

void JumpingState::update(Actor& actor, const int elapsed_time_ms) {
	if (actor.y_vel < 0) {
		actor.setMoveContextState(new FallingState());
	}
	else if (actor.collision_normals.bottom == true)
	{
		actor.setMoveContextState(new OnGroundState());
	}
}

void JumpingState::moveLeft(Actor& actor) {
	if (actor.x_acc >= 0){
		actor.x_acc += -moveAcceleration * inAirSlowdownFactor;
	}
}

void JumpingState::moveRight(Actor& actor) {
	if (actor.x_acc <= 0) {
		actor.x_acc += moveAcceleration * inAirSlowdownFactor;
	}
}
