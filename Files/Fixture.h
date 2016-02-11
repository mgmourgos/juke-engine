#pragma once
#include "Entity.h"
#include "Sprite.h"

//Structural entities that are generally unmoveable
class Fixture : public Entity
{
	std::unique_ptr<Sprite> sprite;
public:

	void draw(const Graphics& graphics, int x_render_pos, int y_render_pos) const override;
	void update(int elapsed_time_ms) override;

	virtual Box getBox() const override;
	virtual void setBox(Box b1) override;

	Fixture(Graphics& graphics, int x_, int y_, int width_, int height_);
	~Fixture();
};

