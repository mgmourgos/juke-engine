#include "OnGroundState.h"
#include "PlayerConstants.h"
#include "FallingState.h"
//const double MaxVelocity = 0.4f;
//const double slowDownFactor = 0.9f;
//const double gravity = 0.0005f;

OnGroundState::OnGroundState()
{
}


OnGroundState::~OnGroundState()
{
}

void OnGroundState::handleCommand(GameActor& game_actor, const Command& command) {

	if (typeid(command) == typeid(MoveRightCommand) ||
		typeid(command) == typeid(MoveLeftCommand)  ||
		typeid(command) == typeid(JumpCommand)) {

		if (typeid(command) == typeid(JumpCommand)) {
			game_actor.setMoveContextState(new JumpingState());
		}

		command.execute(game_actor);
	}
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
