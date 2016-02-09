#pragma once
#include "Command.h"
#include "GameActor.h"

class MoveLeftCommand : public Command
{
public:
	~MoveLeftCommand() {};
	MoveLeftCommand() : Command(MOVE_LEFT, ONHELD) {}
};

class MoveRightCommand : public Command
{
public:
	~MoveRightCommand() override {};
	MoveRightCommand() : Command(MOVE_RIGHT, ONHELD) {}
};

class JumpCommand : public Command
{
public:
	~JumpCommand() override {};
	JumpCommand() : Command(JUMP, ONPRESS) {}
};