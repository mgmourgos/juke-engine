#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Box.h"

class Scene;
class Entity;
class Graphics;

class Camera
{
	double x_pos, y_pos;
	double x_vel, y_vel;
	double x_acc, y_acc;

	//entities that are in camera view and therefore need rendering
	std::vector<std::shared_ptr<const Entity>> cam_entity_queue;

	bool isWithinFrame(const Entity& entity) const;

	Box subject_bounds;

public:
	Camera(int x_pos_, int y_pos_);
	~Camera();

	void draw(const Graphics& graphics) const;
	void update(Scene& scene, int elapsed_time_ms);

	std::pair<int, int> convertWorldToRenderPosition(double x_world_pos, double y_world_pos) const;
};

