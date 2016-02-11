#pragma once

class Actor;

enum CommandName
{
	MOVE_LEFT,
	MOVE_RIGHT,
	JUMP,
	PUSH
};

class Command
{
public:

	virtual ~Command() {};
	enum ActivationType { ONPRESS, ONRELEASE, ONHELD, NONE };

	CommandName getName() const;

	ActivationType getActivationType() const;

protected:
	Command(CommandName name_, ActivationType activation_type_) : name(name_), activation_type(activation_type_){}

	const CommandName name;
	const ActivationType activation_type;
};

