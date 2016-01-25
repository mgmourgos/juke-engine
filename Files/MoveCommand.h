#pragma once
#include "Command.h"
#include "GameActor.h"

/*class MoveCommand : public Command
{
	enum Direction {
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	//Direction direction;

public:
	MoveCommand();
	~MoveCommand();

	//void changeDirection(Direction direction_);
	void execute(GameActor& gameactor);

};*/

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand() { activation_type = ONHELD; }
	void execute(GameActor& gameactor);
};


class MoveRightCommand : public Command
{
public:
	MoveRightCommand() { activation_type = ONHELD; }
	void execute(GameActor& gameactor);
};


class MoveUpCommand : public Command
{
public:
	MoveUpCommand()  { activation_type = ONHELD; }
	void execute(GameActor& gameactor);
};


class MoveDownCommand : public Command
{
public:
	MoveDownCommand()  { activation_type = ONHELD; }
	void execute(GameActor& gameactor);
};