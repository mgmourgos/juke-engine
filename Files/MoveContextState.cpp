#include "MoveContextState.h"
#include "GameActor.h"
#include "PlayerConstants.h"

void MoveContextState::moveLeft(GameActor& game_actor) {
	if (game_actor.x_acc >= 0){
		game_actor.x_acc += -moveAcceleration;
	}
}

void MoveContextState::moveRight(GameActor& game_actor) {
	if (game_actor.x_acc <= 0) {
		game_actor.x_acc += moveAcceleration;
	}
}

void MoveContextState::jump(GameActor& game_actor) {
	game_actor.y_vel = jumpVelocity;
}