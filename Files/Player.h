#pragma once
#include <memory>
#include "Sprite.h"
class Graphics;
class Player
{
	double x, y, xVel, yVel, xAcc, yAcc;
	int xInt, yInt;
	std::unique_ptr<Sprite> sprite;
public:
	void draw(Graphics& graphics);
	void update();
	Player(Graphics& graphics, int x, int y);
	~Player();
};

