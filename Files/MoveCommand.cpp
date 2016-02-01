#include "MoveCommand.h"

void MoveLeftCommand::execute(GameActor& gameactor) {
	gameactor.moveLeft();
}

void MoveRightCommand::execute(GameActor& gameactor) {
	gameactor.moveRight();
}

void JumpCommand::execute(GameActor& gameactor) {
	gameactor.jump();
}

