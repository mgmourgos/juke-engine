#pragma once
#include <memory>
#include <algorithm>
#include "Sprite.h"
#include "GameActor.h"
#include "OnGroundState.h"
#include <memory>
#include <algorithm>

class Command;
class Graphics;

class Player : public GameActor
{
	friend class OnGroundState;
	friend class JumpingState;
	friend class FallingState;

	int xInt, yInt;
	std::unique_ptr<Sprite> sprite;
	
	std::unique_ptr<PlayerState> state;

	//Temporary?
	OnGroundState on_ground;

public:
	Player(Graphics& graphics, int x, int y);
	~Player();

	void draw(Graphics& graphics);
	void update(int elapsed_time_ms);

	void handleCommand(Command& command);

	void setState(PlayerState* new_state);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMoving();
	void jump();

	void setJumping(bool);
};

