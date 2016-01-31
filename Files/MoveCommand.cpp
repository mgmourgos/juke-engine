#include "MoveCommand.h"

void MoveLeftCommand::execute(GameActor& gameactor) {
	gameactor.moveLeft();
}

void MoveRightCommand::execute(GameActor& gameactor) {
	gameactor.moveRight();
}

void MoveUpCommand::execute(GameActor& gameactor) {
	gameactor.moveUp();
}

void MoveDownCommand::execute(GameActor& gameactor) {
	gameactor.moveDown();
}

void JumpCommand::execute(GameActor& gameactor) {
	gameactor.jump();
}

