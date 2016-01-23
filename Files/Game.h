#pragma once
#include <vector>

class Sprite;
class Graphics;

class Game
{
	void eventLoop();
	void draw(Graphics& graphics);
	void update(int elapsed_time_ms);

public:
	Game();
	~Game();
};

