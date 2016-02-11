#include "OnGroundState.h"
#include "PlayerConstants.h"
#include "FallingState.h"
#include "PushingState.h"
#include "Actor.h"
#include <string>

OnGroundState::OnGroundState()
{
}


OnGroundState::~OnGroundState()
{
}

void OnGroundState::handleCommand(Actor& actor, const Command& command) {

	switch(command.getName())
	{
	case MOVE_LEFT:
		moveLeft(actor);
		break;
	case MOVE_RIGHT:
		moveRight(actor);
		break;
	case JUMP:
		jump(actor);
		break;
	case PUSH:
		push(actor);
		break;
	};
}

void OnGroundState::update(Actor& actor, const int elapsed_time_ms) {

	if (actor.collision_normals.bottom == false)
	{
		actor.setMoveContextState(new FallingState());
	}
	else {
		if (fabs(actor.x_vel) <= .001) {
			actor.x_vel = 0;
		}

		if (actor.x_acc == 0) {
			actor.x_vel *= slowDownFactor;
		}
	}
}

void OnGroundState::push(Actor& actor) {
	actor.setMoveContextState(new PushingState());
}
