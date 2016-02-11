#include "Fixture.h"


Fixture::Fixture(Graphics& graphics, int x_, int y_, int width_, int height_) : Entity(x_, y_, width_, height_, UNMOVEABLE)
{
	sprite.reset(new Sprite(graphics, "Files/newPlatform2.bmp", 0, 0, width, height));
}

Fixture::~Fixture()
{
}

void Fixture::draw(const Graphics& graphics, int x_render_pos, int y_render_pos) const {
	sprite->draw(graphics, x_render_pos, y_render_pos);
}

void Fixture::update(int elapsed_time_ms) {
	
	/*if (y_pos > 480) {
		y_pos = 0;
	}
	y_vel = .01;

	y_pos += y_vel * elapsed_time_ms;*/
	
}

Box Fixture::getBox() const {
	Box box(x_pos, y_pos, width, height, 0, 0, 0, 0);
	return box;
}

void Fixture::setBox(Box b1)
{
	x_pos = b1.x;
	y_pos = b1.y;
}