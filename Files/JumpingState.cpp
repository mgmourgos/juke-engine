#include "JumpingState.h"
#include "PlayerConstants.h"

JumpingState::JumpingState()
{
}


JumpingState::~JumpingState()
{
}

void JumpingState::handleCommand(GameActor& game_actor, const Command& command) {

	if (typeid(command) == typeid(MoveRightCommand) ||
		typeid(command) == typeid(MoveLeftCommand)) {
		command.execute(game_actor);
	}
}

void JumpingState::update(GameActor& game_actor, const int elapsed_time_ms) {
	if (game_actor.y_vel > 0) {
		game_actor.setMoveContextState(new FallingState());
	}
}

void JumpingState::moveLeft(GameActor& game_actor) {
	if (game_actor.x_acc >= 0){
		game_actor.x_acc += -moveAcceleration * inAirSlowdownFactor;
	}
}

void JumpingState::moveRight(GameActor& game_actor) {
	if (game_actor.x_acc <= 0) {
		game_actor.x_acc += moveAcceleration * inAirSlowdownFactor;
	}
}
