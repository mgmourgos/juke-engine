#include "MoveContextState.h"
#include "Actor.h"
#include "PlayerConstants.h"
#include "JumpingState.h"

MoveContextState::MoveContextState() : max_velocity(MaxVelocity)
{
}

MoveContextState::MoveContextState(float max_velocity_) : max_velocity(max_velocity_)
{
}

void MoveContextState::moveLeft(Actor& actor) {

	//handles moving left and right
	if (actor.x_acc >= 0){
		actor.x_acc += -moveAcceleration;
	}
}

void MoveContextState::moveRight(Actor& actor) {

	//handles moving left and right
	if (actor.x_acc <= 0) {
		actor.x_acc += moveAcceleration;
	}
}

void MoveContextState::jump(Actor& actor) {
	actor.setMoveContextState(new JumpingState());
	actor.y_vel = jumpVelocity;
}

float MoveContextState::getMaxVelocity() const
{
	return max_velocity;
}