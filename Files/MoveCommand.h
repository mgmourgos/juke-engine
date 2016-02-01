#pragma once
#include "Command.h"
#include "GameActor.h"

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

class JumpCommand : public Command
{
public:
	JumpCommand()  { activation_type = ONPRESS; }
	void execute(GameActor& gameactor);
};