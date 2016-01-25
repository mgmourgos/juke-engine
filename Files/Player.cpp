#include "Player.h"

const double maxVelocity = 0.4f; // pixels / ms
//const float moveAcceleration = 0.0012f; // (pixels / ms) / ms
const float moveAcceleration = 0.0005f; // (pixels / ms) / ms
const double slowDownFactor = 0.9f;
const double jumpVelocity = 0.4f;
const double gravity = 0.0005f;

Player::Player(Graphics& graphics, int x_, int y_) : moveRightLeft(false), moveUpDown(false), jumping(true)
{
	x_pos = x_;
	y_pos = y_;

	sprite.reset(new Sprite(graphics, "Files/Player.bmp", 0, 0, 32, 32));
}


Player::~Player()
{
}

void Player::draw(Graphics& graphics) {
	sprite->draw(graphics, (int)round(x_pos), (int)round(y_pos));
}

void Player::update(int elapsed_time_ms) {
	y_acc = gravity;//y_acc is gravity, and is reset every update so that it cannot be changed.

	x_pos += x_vel * elapsed_time_ms;
	y_pos += y_vel * elapsed_time_ms;
	if (y_pos > 400) {
		jumping = false;
		y_pos = 400;
	}

	x_vel += x_acc * elapsed_time_ms;
	y_vel += y_acc * elapsed_time_ms;

	total_vel = sqrt(x_vel*x_vel + y_vel*y_vel);

	if (x_acc < 0.0f) {
		//x_vel = std::max(x_vel, -fabs((x_vel / total_vel)*(maxVelocity)));
		x_vel = std::max(x_vel, -maxVelocity);
	}
	else if (x_acc > 0.0f) {
		//x_vel = std::min(x_vel, fabs((x_vel / total_vel)*(maxVelocity)));
		x_vel = std::min(x_vel, maxVelocity);
	}
	else {
		if (fabs(x_vel) <= .0001) {
			x_vel = 0;
		}
		else {
			if (!jumping)//only slowdown if not jumping
				x_vel *= slowDownFactor;
		}
	}

	x_acc = 0;
}

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
	if (jumping == false) {
		jumping = true;
		y_vel = -jumpVelocity;
	}
}

void Player::stopMoving() {    //might need this for horizontal and vertical movement not sure
	x_acc = 0;
	y_acc = 0;
}