#pragma once
#include <vector>
#include "Graphics.h"
#include "Sprite.h"
#include "Player.h"
#include "Command.h"

//class Sprite;
class Graphics;

class Game
{
	std::vector<std::shared_ptr<Command>> command_queue;
	std::vector<Sprite> AllSprites;
	Player *player;
	//Sprite BackGround;

	void eventLoop();
	void draw(Graphics& graphics);
	void update(int elapsed_time_ms);
	void executeCommands();

public:
	Game();
	~Game();
};

