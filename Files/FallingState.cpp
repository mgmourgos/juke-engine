#include "FallingState.h"


FallingState::FallingState()
{
}


FallingState::~FallingState()
{
}

void FallingState::handleCommand(GameActor& game_actor, Command& command) {
	if (typeid(command) == typeid(MoveRightCommand) ||
		typeid(command) == typeid(MoveLeftCommand)) {
		command.execute(game_actor);
	}
}

void FallingState::update(GameActor& game_actor, const int elapsed_time_ms) {
}
