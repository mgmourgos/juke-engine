#pragma once
#include <vector>
#include "Graphics.h"
#include "Command.h"
#include "Scene.h"

class Graphics;

class Game
{
	std::vector<std::shared_ptr<Command>> command_queue;

	std::unique_ptr<Scene> current_scene;

	void eventLoop();
	void draw(Graphics& graphics);
	void update(int elapsed_time_ms);
	void executeCommands();

public:
	Game();
	~Game();
};

