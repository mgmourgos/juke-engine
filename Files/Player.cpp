#include "Player.h"
#include "PlayerConstants.h"

const int PLAYER_WIDTH = 25;
const int PLAYER_HEIGHT = 32;

Player::Player(Graphics& graphics, int x_, int y_) : Actor(x_, y_, PLAYER_WIDTH, PLAYER_HEIGHT, MOVEABLE)
{
	sprite.reset(new Sprite(graphics, "Files/ghostSheet.bmp", 0, 0, width, height));

	move_context_state = std::make_unique<OnGroundState>();
}


Player::~Player()
{
}

void Player::draw(const Graphics& graphics, int x_render_pos, int y_render_pos) const {
	sprite->draw(graphics, x_render_pos, y_render_pos);
}


void Player::handleCommand(const Command& command) {
	move_context_state->handleCommand(*this, command);
}

void Player::update(int elapsed_time_ms) {
	
  	double remaining_time_ms = elapsed_time_ms;

	for (auto& collision : collision_vector)
	{
		setCollisionNormal(collision->normal);
	}

	Box result_box = physics.update(collision_vector, getBox(), move_context_state->getMaxVelocity(), elapsed_time_ms);
	setBox(result_box);

	collision_vector.clear();

	move_context_state->update(*this, remaining_time_ms);

	x_acc = 0;//Acceleration is only set actively(by commands)
			  //So we set it back to zero each frame

	collision_normals.reset();
}


void Player::setMoveContextState(MoveContextState* new_state) {
	move_context_state->onExit(*this);
	move_context_state.reset(new_state);
	move_context_state->onEntry(*this);
}
