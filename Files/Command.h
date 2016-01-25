#pragma once

class GameActor;

class Command
{

public:
	enum ActivationType { ONPRESS, ONRELEASE, ONHELD, NONE };

	Command();
	~Command();
	virtual void execute(GameActor& gameactor) = 0;

	ActivationType getActivationType();

protected:
	ActivationType activation_type;
};

