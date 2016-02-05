#include "MoveCommand.h"

void MoveLeftCommand::execute(GameActor& gameactor) const {
	gameactor.moveLeft();
}

void MoveRightCommand::execute(GameActor& gameactor) const {
	gameactor.moveRight();
}

void JumpCommand::execute(GameActor& gameactor) const {
	gameactor.jump();
}

