#pragma once
#include <memory>
#include <algorithm>
#include "Sprite.h"
#include "GameActor.h"
#include "OnGroundState.h"
//#include "MoveContextState.h"
#include <memory>
#include <algorithm>

class Command;
class Graphics;

class Player : public GameActor
{
	friend class OnGroundState;
	friend class JumpingState;
	friend class FallingState;
	friend class MoveContextState;

	int xInt, yInt;
	std::unique_ptr<Sprite> sprite;
	
	std::unique_ptr<MoveContextState> move_context_state;

public:
	Player(Graphics& graphics, int x, int y);
	~Player();

	void draw(Graphics& graphics);
	void update(int elapsed_time_ms);

	void handleCommand(Command& command);

	void setMoveContextState(MoveContextState* new_state);

	void moveLeft();
	void moveRight();
	void jump();

	void setJumping(bool);
};

