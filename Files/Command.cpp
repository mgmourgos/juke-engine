#include "Command.h"

CommandName Command::getName() const
{
	return name;
}

Command::ActivationType Command::getActivationType() const 
{
	return activation_type;
}
