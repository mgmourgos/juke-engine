#include "MoveCommand.h"


/*MoveCommand::MoveCommand() : direction()
{
}


MoveCommand::~MoveCommand()
{
}

void MoveCommand::changeDirection(Direction direction_) {
	direction = direction_;
}

void MoveCommand::execute(GameActor& gameactor) {
	
}*/

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
