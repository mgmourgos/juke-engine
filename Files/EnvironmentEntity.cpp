#include "EnvironmentEntity.h"


EnvironmentEntity::EnvironmentEntity(Graphics& graphics, int x_, int y_, int width_, int height_) : Entity(x_, y_)
{
	x_pos = x_;
	y_pos = y_;
	width = width_;
	height = height_;
	x_vel = 0;
	y_vel = 0;
	sprite.reset(new Sprite(graphics, "Files/Platform.bmp", 0, 0, width, height));
}


EnvironmentEntity::~EnvironmentEntity()
{
}

void EnvironmentEntity::draw(const Graphics& graphics) const {
	sprite->draw(graphics, (int)round(x_pos), (int)round(y_pos));
}

void EnvironmentEntity::update(int elapsed_time_ms) {
	
	if (y_pos < 50) {
		y_pos = 550;
	}
	y_vel = -.01;

	y_pos += y_vel * elapsed_time_ms;
	
}