#pragma once
#include <vector>
#include <memory>
#include "Command.h"
#include "Sprite.h"
#include "Entity.h"
#include "Camera.h"

class Graphics;

class Scene
{
	friend class Camera;

	int width, height;

	//std::vector<std::shared_ptr<Command>> command_queue;
	std::vector<Sprite> AllSprites;
	std::vector<std::shared_ptr<Entity>> entity_queue;
	std::vector < std::shared_ptr<GameActor>>game_actor_queue;

	std::unique_ptr<Camera> camera;

	std::shared_ptr<Entity> camera_subject;

public:
	Scene(Graphics& graphics, int w, int h);
	~Scene();

	void draw(const Graphics& graphics) const;
	void update(int elapsed_time_ms);

	void executeCommands(std::vector<std::shared_ptr<Command>>& command_queue);
};

