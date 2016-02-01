#pragma once
#include <vector>
#include "Graphics.h"
#include "Sprite.h"
#include "Player.h"
#include "Command.h"
#include "Entity.h"
#include "Box.h"

//class Sprite;
class Graphics;

class Game
{
	std::vector<std::shared_ptr<Command>> command_queue;
	std::vector<Sprite> AllSprites;
	std::vector<std::shared_ptr<Entity>> entity_queue;
	std::vector < std::shared_ptr<GameActor>>gameActor_queue;
	//Sprite BackGround;

	void eventLoop();
	void draw(Graphics& graphics);
	void update(int elapsed_time_ms);
	void executeCommands();


	bool doCollision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);

	//float SweptAABB(Box b1, Box b2, float &normalx, float &normaly);
	Box getBroadphaseBox(Box b1, int elapsedTime);
	bool checkBroadphase(Box b1, Box b2, int elapsed_time_ms);

public:
	Game();
	~Game();
};

