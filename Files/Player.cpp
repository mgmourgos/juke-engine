#include "Player.h"
#include "PlayerConstants.h"

Player::Player(Graphics& graphics, int x_, int y_)
{
	x_pos = x_;
	y_pos = y_;

	y_acc = gravity;

	width = 25;
	height = 32;
	sprite.reset(new Sprite(graphics, "Files/Player.bmp", 0, 0, width, height));

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


void Player::setJumping(bool j_) {
	jumping = j_;
}


void Player::update(int elapsed_time_ms) {

  	double remaining_time_ms = elapsed_time_ms;

	for (auto& collision : collision_vector)
	{
		setCollisionNormal(collision->normal);
	}

	for (auto& collision : collision_vector)
	{
		handleCollision(*collision, remaining_time_ms, elapsed_time_ms);
	}

	collision_vector.clear();

	doPhysics(remaining_time_ms, MaxVelocity);

	move_context_state->update(*this, remaining_time_ms);

	x_acc = 0;//Acceleration is only set actively(by commands)
			  //So we set it back to zero each frame

	collision_normals.reset();
}


void Player::setMoveContextState(MoveContextState* new_state) {
	move_context_state.reset(new_state);
}

/////Command executions
void Player::moveLeft() {
	move_context_state->moveLeft(*this);
}

void Player::moveRight() {
	move_context_state->moveRight(*this);
}

void Player::jump() {
	move_context_state->jump(*this);
}
