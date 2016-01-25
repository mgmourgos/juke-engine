#pragma once
#include <memory>
#include "Sprite.h"
#include "GameActor.h"
#include <algorithm>

class Graphics;

class Player : public GameActor
{
	int xInt, yInt;
	std::unique_ptr<Sprite> sprite;

	bool moveRightLeft;
	bool moveUpDown;

public:
	Player(Graphics& graphics, int x, int y);
	~Player();

	void draw(Graphics& graphics);
	void update(int elapsed_time_ms);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMoving();
};

