#include "OnGroundState.h"
#include "PlayerConstants.h"
#include "FallingState.h"
#include "PushCommand.h"
#include "MoveCommand.h"
#include "PushingState.h"
#include <string>

OnGroundState::OnGroundState()
{
}


OnGroundState::~OnGroundState()
{
}

void OnGroundState::handleCommand(GameActor& game_actor, const Command& command) {

	switch(command.getName())
	{
	case MOVE_LEFT:
		moveLeft(game_actor);
		break;
	case MOVE_RIGHT:
		moveRight(game_actor);
		break;
	case JUMP:
		jump(game_actor);
		break;
	case PUSH:
		push(game_actor);
		break;
	};
}

void OnGroundState::update(GameActor& game_actor, const int elapsed_time_ms) {

	if(game_actor.collision_normals.bottom == false)
	{
		game_actor.setMoveContextState(new FallingState());
	}
	else {
		if (fabs(game_actor.x_vel) <= .001) {
			game_actor.x_vel = 0;
		}

		if (game_actor.x_acc == 0) {
			game_actor.x_vel *= slowDownFactor;
		}
	}
}

void OnGroundState::push(GameActor& game_actor) {
	game_actor.setMoveContextState(new PushingState());
}
