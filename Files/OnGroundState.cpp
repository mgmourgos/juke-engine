#include "OnGroundState.h"

const double maxVelocity = 0.4f;
const double slowDownFactor = 0.9f;
const double gravity = 0.0005f;

OnGroundState::OnGroundState()
{
}


OnGroundState::~OnGroundState()
{
}

void OnGroundState::handleCommand(GameActor& game_actor, Command& command) {

	if (typeid(command) == typeid(MoveRightCommand) ||
		typeid(command) == typeid(MoveLeftCommand)  ||
		typeid(command) == typeid(MoveUpCommand)    ||
		typeid(command) == typeid(MoveDownCommand)  ||
		typeid(command) == typeid(JumpCommand)) {

		if (typeid(command) == typeid(JumpCommand)) {
			game_actor.setState(new JumpingState());
		}

		command.execute(game_actor);
	}
}

void OnGroundState::update(GameActor& game_actor, const int elapsed_time_ms) {

	if (fabs(game_actor.x_vel) <= .001) {
		game_actor.x_vel = 0;
	}

	if (game_actor.x_acc == 0) {
		game_actor.x_vel *= slowDownFactor;
	}
}
