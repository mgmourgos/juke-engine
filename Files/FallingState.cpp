#include "FallingState.h"
#include "PlayerConstants.h"
#include "OnGroundState.h"

FallingState::FallingState()
{
}


FallingState::~FallingState()
{
}

void FallingState::handleCommand(GameActor& game_actor, const Command& command) {

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

void FallingState::update(GameActor& game_actor, const int elapsed_time_ms) {

	if (game_actor.collision_normals.bottom == true)
	{
		game_actor.setMoveContextState(new OnGroundState());
	}
}

void FallingState::moveLeft(GameActor& game_actor) {
	if (game_actor.x_acc >= 0){
		game_actor.x_acc += -moveAcceleration * inAirSlowdownFactor;
	}
}

void FallingState::moveRight(GameActor& game_actor) {
	if (game_actor.x_acc <= 0) {
		game_actor.x_acc += moveAcceleration * inAirSlowdownFactor;
	}
}
