#pragma once
#include "Command.h"

class PushCommand : public Command
{
public:
	~PushCommand() {};
	PushCommand() : Command(PUSH, ONHELD) {};
};

