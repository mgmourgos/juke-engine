#include "Camera.h"
#include "Game.h"
#include "Entity.h"
#include "Scene.h"
#include "GameConstants.h"

const double PLAYER_X_BOUND_PERCENTAGE = .4;
const double PLAYER_Y_BOUND_PERCENTAGE = .3;

Camera::Camera(int x_pos_, int y_pos_) : x_pos(x_pos_), y_pos(y_pos_), x_vel(0), y_vel(0), x_acc(0), y_acc(0)
{
	subject_bounds.x = x_pos + SCREEN_WIDTH * PLAYER_X_BOUND_PERCENTAGE;
	subject_bounds.w = SCREEN_WIDTH - 2 * (SCREEN_WIDTH * PLAYER_X_BOUND_PERCENTAGE);

	subject_bounds.y = y_pos - SCREEN_HEIGHT * PLAYER_Y_BOUND_PERCENTAGE;
	subject_bounds.h = SCREEN_HEIGHT - 2 * (SCREEN_HEIGHT * PLAYER_Y_BOUND_PERCENTAGE);


}

Camera::~Camera()
{
}

void Camera::draw(const Graphics& graphics) const
{
	std::pair<int, int> render_pos;

	for(auto entity : cam_entity_queue)
	{
		render_pos = convertWorldToRenderPosition(entity->x_pos, entity->y_pos);
		entity->draw(graphics, render_pos.first, render_pos.second);
	}
}

void Camera::update(Scene& scene, int elapsed_time_ms)
{
	cam_entity_queue.clear();

	for(auto entity : scene.entity_queue)
	{
		if (isWithinFrame(*entity)) {
			cam_entity_queue.push_back(entity);
		}
	}

	//~~~~~~~~~Update Camera position based on player position~~~~~~~~~~
	Box camera_subject = scene.camera_subject->getBox();

	//if camera_subject is out of bounds in x direction
	if(camera_subject.x < subject_bounds.x)
	{
		x_pos -= subject_bounds.x - camera_subject.x;

	} else if ((camera_subject.x + camera_subject.w) > (subject_bounds.x + subject_bounds.w))
	{
		x_pos += (camera_subject.x + camera_subject.w) - (subject_bounds.x + subject_bounds.w);
	}

	//if camera_subject is out of bounds in y direction
	if(camera_subject.y > subject_bounds.y)
	{
		y_pos += camera_subject.y - subject_bounds.y;

	} else if ((camera_subject.y - camera_subject.h) < (subject_bounds.y - subject_bounds.h))
	{
		y_pos -= (subject_bounds.y - subject_bounds.h) - (camera_subject.y - camera_subject.h);
	}

	//~~~~~~~~~Ensures that camera stays within bounds of scene~~~~~~~~~~~
	if (x_pos < 0) {
		x_pos = 0;
		x_vel = 0;
	}
	else if ((x_pos + SCREEN_WIDTH) > scene.width) {
		x_pos = scene.width - SCREEN_WIDTH;
		x_vel = 0;
	}

	if (y_pos - SCREEN_HEIGHT < 0) {
		y_pos = SCREEN_HEIGHT;
		y_vel = 0;
	}
	else if (y_pos > scene.height) {
		y_pos = scene.height;
		y_vel = 0;
	}

	//~~~~~~~~~~Update player bounds~~~~~~~~~~~~~~
	subject_bounds.x = x_pos + SCREEN_WIDTH * PLAYER_X_BOUND_PERCENTAGE;
	subject_bounds.y = y_pos - SCREEN_HEIGHT * PLAYER_Y_BOUND_PERCENTAGE;
}

std::pair<int, int> Camera::convertWorldToRenderPosition(double x_world_pos, double y_world_pos) const
{
	std::pair<int, int> render_pos;

	render_pos.first = round(x_world_pos - x_pos);
	render_pos.second = round(y_pos - y_world_pos);

	return render_pos;
}

bool Camera::isWithinFrame(const Entity& entity) const
{
	Box entity_box = entity.getBox();

	//entity is outside bounds of camera (screen)
	if((entity_box.x + entity_box.w) < x_pos || entity_box.x > x_pos + SCREEN_WIDTH ||
		(entity_box.y - entity_box.h) > y_pos || entity_box.y < (y_pos - SCREEN_HEIGHT))
	{
		return false;
	}

	return true;

}