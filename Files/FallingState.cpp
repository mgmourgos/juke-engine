#include "FallingState.h"
#include "PlayerConstants.h"

FallingState::FallingState()
{
}


FallingState::~FallingState()
{
}

void FallingState::handleCommand(GameActor& game_actor, const Command& command) {
	if (typeid(command) == typeid(MoveRightCommand) ||
		typeid(command) == typeid(MoveLeftCommand)) {
		command.execute(game_actor);
	}
}

void FallingState::update(GameActor& game_actor, const int elapsed_time_ms) {
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
