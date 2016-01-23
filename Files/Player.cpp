#include "Player.h"

Player::Player(Graphics& graphics, int x_ , int y_)
{
	x = x_;
	y = y_;
	//sprite = std::make_unique<Sprite>(graphics, "Files\Player.bmp", x, y, 32, 32);
	sprite.reset(new Sprite(graphics, "Files/Player.bmp", 0, 0, 32, 32));
}


Player::~Player()
{
}

void Player::draw(Graphics& graphics) {
	sprite->draw(graphics, (int)round(x), (int)round(y));
}

void Player::update() {

}