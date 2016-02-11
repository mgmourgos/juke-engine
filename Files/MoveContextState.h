#pragma once
#include "PlayerState.h"

class MoveContextState : public PlayerState
{
protected:
	const float max_velocity;

public:
	MoveContextState();
	MoveContextState(float max_velocity_);

	virtual void handleCommand(Actor& actor, const Command& command) override = 0;
	virtual void update(Actor& actor, const int elapsed_time_ms) override = 0;
	
	virtual void moveLeft(Actor& actor);
	virtual void moveRight(Actor& actor);
	virtual void jump(Actor& actor);
	virtual void push(Actor& actor) {}  //only done in ongroundstate

	float getMaxVelocity() const;
};

