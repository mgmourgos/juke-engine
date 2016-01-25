#include "Player.h"

const double maxVelocity = 0.4f; // pixels / ms
//const float moveAcceleration = 0.0012f; // (pixels / ms) / ms
const float moveAcceleration = 0.0005f; // (pixels / ms) / ms
const double slowDownFactor = 0.9f;

Player::Player(Graphics& graphics, int x_ , int y_) : moveRightLeft(false), moveUpDown(false)
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
	x_pos += x_vel * elapsed_time_ms;
	y_pos += y_vel * elapsed_time_ms;

	x_vel += x_acc * elapsed_time_ms;
	y_vel += y_acc * elapsed_time_ms;

	total_vel = sqrt(x_vel*x_vel + y_vel*y_vel);

	if (x_acc < 0.0f) {
		x_vel = std::max(x_vel, -fabs((x_vel / total_vel)*(maxVelocity)));
	}
	else if (x_acc > 0.0f) {
		x_vel = std::min(x_vel, fabs((x_vel / total_vel)*(maxVelocity)));
	}
	else {
		if (fabs(x_vel) <= .0001) {
			x_vel = 0;
		}
		else {
			x_vel *= slowDownFactor;
		}
	}

	if (y_acc < 0.0f) {
		y_vel = std::max(y_vel, -fabs((y_vel / total_vel)*(maxVelocity)));
	}
	else if (y_acc > 0.0f) {
		y_vel = std::min(y_vel, fabs((y_vel / total_vel)*(maxVelocity)));
	}
	else {
		if (fabs(y_vel) <= .0001) {
			y_vel = 0;
		}
		else {
			y_vel *= slowDownFactor;
		}
	}
	x_acc = 0;
	y_acc = 0;
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

void Player::stopMoving() {    //might need this for horizontal and vertical movement not sure
	x_acc = 0;
	y_acc = 0;
}