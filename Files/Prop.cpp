#include "Prop.h"
#include "PlayerConstants.h"

const int SCAFFOLD_WIDTH = 50;
const int SCAFFOLD_HEIGHT = 100;

Prop::Prop(Graphics& graphics, int x_, int y_) : Entity(x_, y_, SCAFFOLD_WIDTH, SCAFFOLD_HEIGHT, PUSHABLE),
x_vel(0), y_vel(0), x_acc(0), y_acc(gravity)
{
	sprite.reset(new Sprite(graphics, "Files/Scaffold.bmp" , 0, 0, width, height));
}

Prop::~Prop()
{
}

void Prop::update(int elapsed_time_ms)
{
	double remaining_time_ms = elapsed_time_ms;

	/*for (auto& collision : collision_vector)
	{
		setCollisionNormal(collision->normal);
	}*/

	Box result_box = physics.update(collision_vector, getBox(), PUSH_MAX_VELOCITY, elapsed_time_ms);
	setBox(result_box);

	collision_vector.clear();

	x_vel = 0;

	x_acc = 0;//Acceleration is only set actively(by commands)
	//So we set it back to zero each frame

	//collision_normals.reset();
}

void Prop::draw(const Graphics& graphics, int x_render_pos, int y_render_pos) const
{
	sprite->draw(graphics, x_render_pos, y_render_pos);
}

Box Prop::getBox() const {
	Box box(x_pos, y_pos, width, height, x_vel, y_vel, x_acc, y_acc);
	return box;
}

void Prop::setBox(Box b1)
{
	x_pos = b1.x;
	y_pos = b1.y;
	x_vel = b1.vx;
	y_vel = b1.vy;
	x_acc = b1.ax;
	y_acc = b1.ay;
}