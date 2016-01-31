#include "Player.h"

const double maxVelocity = 0.4f; // pixels / ms
//const float moveAcceleration = 0.0012f; // (pixels / ms) / ms
const float moveAcceleration = 0.0005f; // (pixels / ms) / ms
const double slowDownFactor = 0.9f;
const double jumpVelocity = 0.4f;
const double gravity = 0.0005f;

Player::Player(Graphics& graphics, int x_, int y_)
{
	x_pos = x_;
	y_pos = y_;

	y_acc = gravity;

	width = 25;
	height = 32;
	sprite.reset(new Sprite(graphics, "Files/Player.bmp", 0, 0, width, height));

	state = std::make_unique<OnGroundState>();
}


Player::~Player()
{
}

void Player::draw(Graphics& graphics) {
	sprite->draw(graphics, (int)round(x_pos), (int)round(y_pos));
}


void Player::handleCommand(Command& command) {
	state->handleCommand(*this, command);
}


void Player::setJumping(bool j_) {
	jumping = j_;
}


void Player::update(int elapsed_time_ms) {
	if (x_acc < 0.0f) {
		x_vel = std::max(x_vel, -maxVelocity);
	}
	else if (x_acc > 0.0f) {
		x_vel = std::min(x_vel, maxVelocity);
	}

	doPhysics(elapsed_time_ms);

	state->update(*this, elapsed_time_ms);

	x_acc = 0;

	/////Temporary
	if (y_pos > 400) {
		y_pos = 400;
		y_vel = 0;
		state.reset(new OnGroundState());
	}
}


void Player::setState(PlayerState* new_state) {
	state.reset(new_state);
}




/////Command executions
void Player::moveLeft() {
	if (x_acc >= 0){
		x_acc += -moveAcceleration;
	}
}

void Player::moveRight() {
	if (x_acc <= 0) {
		x_acc += moveAcceleration;
	}
}

void Player::moveDown() {
	if (y_acc <= 0) {
		y_acc += moveAcceleration;
	}
}

void Player::moveUp() {
	
	if (y_acc >= 0) {
		y_acc += -moveAcceleration;
	}
}

void Player::jump() {
	y_vel = -jumpVelocity;
}

void Player::stopMoving() {    //might need this for horizontal and vertical movement not sure
	x_acc = 0;
	y_acc = 0;
}