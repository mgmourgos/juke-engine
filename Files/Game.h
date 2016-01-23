#pragma once
#include <vector>
#include "Graphics.h"
#include "Sprite.h"
#include "Player.h"

class Sprite;
class Graphics;

class Game
{
	
	std::vector<Sprite> AllSprites;
	Graphics graphics;
	Player *player;
	//Sprite BackGround;

	void eventLoop();
	void draw(Graphics& graphics);
	void update(int elapsed_time_ms);

public:
	Game();
	~Game();
};

