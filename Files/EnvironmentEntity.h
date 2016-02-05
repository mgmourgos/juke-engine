#pragma once
#include "Entity.h"
#include "Sprite.h"
class EnvironmentEntity :
	public Entity
{
	std::unique_ptr<Sprite> sprite;
public:

	void draw(const Graphics& graphics) const override;
	void update(int elapsed_time_ms) override;

	EnvironmentEntity(Graphics& graphics, int x_, int y_, int width_, int height_);
	~EnvironmentEntity();
};

