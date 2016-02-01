#include "Player.h"
#include "PlayerConstants.h"
/*
const double MaxVelocity = 0.4f; // pixels / ms
//const float moveAcceleration = 0.0012f; // (pixels / ms) / ms
const float moveAcceleration = 0.0005f; // (pixels / ms) / ms
const double slowDownFactor = 0.9f;
const double jumpVelocity = 0.4f;
const double gravity = 0.0005f;*/

Player::Player(Graphics& graphics, int x_, int y_)
{
	x_pos = x_;
	y_pos = y_;

	y_acc = gravity;
	std::cout << "set Gravity in player class constructor		Derived Class" << std::endl;

	width = 25;
	height = 32;
	sprite.reset(new Sprite(graphics, "Files/Player.bmp", 0, 0, width, height));

	move_context_state = std::make_unique<OnGroundState>();
}


Player::~Player()
{
}

void Player::draw(Graphics& graphics) {
	sprite->draw(graphics, (int)round(x_pos), (int)round(y_pos));
}


void Player::handleCommand(Command& command) {
	move_context_state->handleCommand(*this, command);
}


void Player::setJumping(bool j_) {
	jumping = j_;
}


void Player::update(int elapsed_time_ms) {

	doPhysics(elapsed_time_ms, MaxVelocity);

	move_context_state->update(*this, elapsed_time_ms);

	x_acc = 0;//Acceleration is only set actively(by commands)
			  //So we set it back to zero each frame
	//y_acc = gravity;
	/////Temporary
	/*
	if (y_pos > 400) {
		y_pos = 400;
		y_vel = 0;
		move_context_state.reset(new OnGroundState());
	}*/
}


void Player::setMoveContextState(MoveContextState* new_state) {
	move_context_state.reset(new_state);
}




/////Command executions
void Player::moveLeft() {
	move_context_state->moveLeft(*this);
}

void Player::moveRight() {
	move_context_state->moveRight(*this);
}

void Player::jump() {
	move_context_state->jump(*this);
}
