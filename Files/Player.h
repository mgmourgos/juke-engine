#pragma once
#include <memory>
#include "Sprite.h"
#include "GameActor.h"
#include "OnGroundState.h"

class Command;
class Graphics;

class Player : public GameActor
{
	friend class OnGroundState;
	friend class JumpingState;
	friend class FallingState;
	friend class MoveContextState;

	std::unique_ptr<Sprite> sprite;
	
	std::unique_ptr<MoveContextState> move_context_state;

public:
	Player(Graphics& graphics, int x, int y);
	~Player();

	void draw(const Graphics& graphics, int x_render_pos, int y_render_pos) const override;
	void update(int elapsed_time_ms) override;

	void handleCommand(const Command& command) override;

	void setMoveContextState(MoveContextState* new_state) override;

	void moveLeft() override;
	void moveRight() override;
	void jump() override;

	void setJumping(bool);
};

