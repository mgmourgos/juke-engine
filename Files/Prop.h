#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Physics.h"

class Prop : public Entity
{
	std::unique_ptr<Sprite> sprite;

protected:

	double x_vel, y_vel;
	double x_acc, y_acc;

	Physics physics;

public:
	Prop(Graphics& graphics, int x_, int y_);
	~Prop();

	void update(int elapsed_time_ms) override;
	void draw(const Graphics& graphics, int x_render_pos, int y_render_pos) const override;

	Box getBox() const override;
	void setBox(Box b1) override;

	void handleCollision(CollisionData& collision_data, double& remaining_time_ms, int elapsed_time_ms);
};

