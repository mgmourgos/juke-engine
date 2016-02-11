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

	for (auto& collision : collision_vector)
	{
		setCollisionNormal(collision->normal);
	}

	for (auto& collision : collision_vector)
	{
		handleCollision(*collision, remaining_time_ms, elapsed_time_ms);
	}

	collision_vector.clear();

	Box result_box = physics.actPhysicsOn(remaining_time_ms, PUSH_MAX_VELOCITY, getBox());
	setBox(result_box);

	x_vel = 0;

	x_acc = 0;//Acceleration is only set actively(by commands)
	//So we set it back to zero each frame

	collision_normals.reset();
}

void Prop::draw(const Graphics& graphics, int x_render_pos, int y_render_pos) const
{
	sprite->draw(graphics, x_render_pos, y_render_pos);
}

void Prop::handleCollision(CollisionData& collision_data, double& remaining_time_ms, int elapsed_time_ms)
{
	double offset_collision_time = collision_data.collision_time - .000000001;

	if ((collision_data.normal == RIGHT || collision_data.normal == LEFT) && collision_data.type == PUSHING)
	{
		//Moving platforms will not work
		x_pos += offset_collision_time * x_vel;

		x_vel = collision_data.x_vel_obj;

		//can't move in y if colliding with obj in y velocity direction

		if (!(collision_normals.bottom && y_vel < 0) && !(collision_normals.top && y_vel > 0))  //clear this up
		{
			y_pos += offset_collision_time * y_vel;
		}
		//x_vel = 0;
		remaining_time_ms -= offset_collision_time;
	}
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