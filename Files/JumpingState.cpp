#include "JumpingState.h"


JumpingState::JumpingState()
{
}


JumpingState::~JumpingState()
{
}

void JumpingState::handleCommand(GameActor& game_actor, Command& command) {

	if (typeid(command) == typeid(MoveRightCommand) ||
		typeid(command) == typeid(MoveLeftCommand)) {
		command.execute(game_actor);
	}
}

void JumpingState::update(GameActor& game_actor, const int elapsed_time_ms) {
	if (game_actor.y_vel > 0) {
		game_actor.setState(new FallingState());
	}
}