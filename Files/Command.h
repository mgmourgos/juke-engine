#pragma once
class Command
{
public:
	Command();
	~Command();
	virtual void execute() = 0;
};

