#include "Game.h"
#include <SDL.h>
#include <math.h>
#include "Graphics.h"
#include "Sprite.h"
#include <iostream>
#include "InputHandler.h"
#include "EnvironmentEntity.h"

namespace {
	const int FPS = 60;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	eventLoop();
	AllSprites.clear();
}

Game::~Game() {
	SDL_Quit();
}

void Game::eventLoop() {

	Graphics graphics;
	InputHandler input;
	
	Sprite BackGround(graphics, "Files/Background.bmp", 0, 0, 640, 432);

	std::shared_ptr<Player> player = std::make_shared<Player>(graphics, 320, 240);
	entity_queue.push_back(player);
	gameActor_queue.push_back(player);

	std::shared_ptr<EnvironmentEntity> platform = std::make_shared<EnvironmentEntity>(graphics, 350, 350, 50, 20);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 400, 240, 100, 20);
	entity_queue.push_back(platform);//All game objects are in the entity queue
									//All gameActors are in gameActor_queue

	AllSprites.push_back(BackGround);
	
	bool running = true;
	int last_update_time = SDL_GetTicks();

	while (running) {
		const int start_time_ms = SDL_GetTicks();
		input.beginNewFrame();





		running = input.getCommandsFromInput(command_queue);
		//give commands the id of gameactor to execute
		//ai.getCmds(command_queue)
		//command_queue.push_back()

		executeCommands();

		const int current_time_ms = SDL_GetTicks();

		//graphics.clear();







		update(current_time_ms - last_update_time);
		last_update_time = current_time_ms;

		draw(graphics);
		





		const int ms_per_frame = 1000/*ms*/ / FPS;
		const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
		if (elapsed_time_ms < ms_per_frame) {
			SDL_Delay(ms_per_frame - elapsed_time_ms);   //delays for 1/60th of a second //10 ms or less of granularity
		}
	}//while running
}

void Game::executeCommands() {
	for (auto command : command_queue) {
		//command->execute(*gameActor_queue[0]);
		gameActor_queue[0]->handleCommand(*command);
	}
	command_queue.clear();
}

void Game::draw(Graphics& graphics) {
	graphics.clear();
	for (size_t i = 0; i < AllSprites.size(); i++) {
		AllSprites[i].draw(graphics, 0, 0);
	}
	for (auto &entity : entity_queue) {
		entity->draw(graphics);
	}

	graphics.flip();
}

void Game::update(int elapsed_time_ms) {
	//check collisions
	for (auto &entity1 : entity_queue) {
		for (auto &entity2 : entity_queue) {
			if (entity1 != entity2) {
				//checkCollision(entity1, entity2);
				bool isCollisionPossible = checkBroadphase(entity1->getBox(), entity2->getBox(), elapsed_time_ms);
				if (isCollisionPossible) {
					std::cout << "Possible Collision" << std::endl;
					doCollision(entity1, entity2);
				}
				else {
					//std::cout << "Not Possible" << std::endl;
				}
			}
		}
	}


	for (auto &entity : entity_queue) {
		entity->update(elapsed_time_ms);
	}
}

bool Game::checkBroadphase(Box b1, Box b2, int elapsed_time_ms) {
	if (b1.vx == 0.0f && b1.vy == 0.0f) {//added this so only moving objs are checked
		return false;
	}
	Box broad = doPhysics(b1, elapsed_time_ms);//returns the broadphase box
	//broad.print();

	//compare broad with b2;
	if (broad.x > (b2.x + b2.w)) {
		//then no collision
		return false;
	}
	if ((broad.x + broad.w) < b2.x) {
		return false;
	}
	if ((broad.y + broad.h) < b2.y) {
		return false;
	}
	if (broad.y > (b2.y + b2.h)) {
		return false;
	}

	return true;
}

Box Game::doPhysics(Box b1, int elapsedTime) {
	//returns the box resulting from the x anad y velocities over time
	Box returnBox;
	returnBox.x = b1.x + b1.vx * elapsedTime;
	returnBox.y = b1.y + b1.vy * elapsedTime;
	returnBox.w = b1.w;
	returnBox.h = b1.h;
	/*return returnBox;*/


	//want this to return the broadphase box...
	Box box;
	if (b1.vx < 0) {
		box.x = returnBox.x;
		box.w = b1.x - returnBox.x + b1.w;
	}
	else {
		box.x = b1.x;
		box.w = returnBox.x - b1.x + b1.w;
	}

	if (b1.vy < 0) {
		box.y = returnBox.y;
		box.h = b1.y - returnBox.y + b1.h;
	}
	else {
		box.y = b1.y;
		box.h = returnBox.y - b1.y + b1.h;
	}
	return box;
}

bool Game::doCollision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2) {
	//Function implements a swept AABB algorithm
	Box b1, b2;
	b1 = e1.get()->getBox();
	b2 = e2.get()->getBox();
	if (b1.vx == 0.0f && b1.vy == 0.0f) {//added this so only moving objs are checked
		return false;
	}

	bool s1, s2, s3, s4;
	s1 = s2 = s3 = s4 = false;


	/*		State Diagram:

			1	 |1 |	1
			2	 |  |	4
			-----~~~~-----
			2	 |b2|   4
			-----~~~~-----
			2	 |  |	4
			3	 | 3|	3
	*/
	//checks which side of b2 b1 is on.
	if (b1.x > (b2.x + b2.w)) {//then b1 is to the right of b2		in state 4
		//then no collision
		s4 = true;
	} else
	if ((b1.x + b1.w) < b2.x) {//then b1 is to the left of b2		in state 2
		s2 = true;
	}

	if ((b1.y + b1.h) < b2.y) {//then b1 is above b2				in state 1
		s1 = true;
	} else
	if (b1.y > (b2.y + b2.h)) {//then b1 is below b2				in state 3
		s3 = true;
	}

	

		//above or below b2 approaching from left   or	 above or below b2 approaching from right
	if ((b2.x <= b1.x + b1.w && s4 == false) || (b1.x <= b2.x + b2.w && s2 == false))  {
		//then b1 below b2 but within y axis sides of b2
		if (s3 == true) {
			//then b1 below b2
			Box b1After;
			b1After.vx = b1.vx;
			b1After.y = b2.y + b2.h + .01;
			double deltaY = b1.y - b1After.y;
			//double elapedTime = -(deltaY / b1.vy);
			//b1After.x = b1.x + elapedTime * b1.vx;
			b1After.x = b1.x;
			b1After.vy = 0;
			e1.get()->setBox(b1After);
		}
		else if (s1 == true) {
			//then b1 above b2
			Box b1After;
			b1After.vx = b1.vx;
			b1After.y = b2.y - b1.h - .1;
			double deltaY = b1After.y + b1.h - b1.y + b1.h;
			//double elapedTime = (deltaY / b1.vy);
			//b1After.x = b1.x; //+ elapedTime * b1.vx;
			b1After.x = b1.x;
			//b1After.vy = 0;
			e1.get()->setBox(b1After);
			//e1.get()->setToUpdate(false); //CHANGES A LOT
			
		}
	}
	return false;
}

/*
float Game::SweptAABB(Box b1, Box b2, float &normalx, float &normaly) {
	//More info: http://www.gamedev.net/page/resources/_/technical/game-programming/swept-aabb-collision-detection-and-response-r3084
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	//Find distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f) {
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else {
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vx > 0.0f) {
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
	}
	else {
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);
	}


	float xEntry, yEntry;
	float xExit, yExit;

	//Find time of collision and time of leaving for each axis
	if (b1.vx == 0.0f) {
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else {
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}
	if (b1.vy == 0.0f) {
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else {
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	//find earliest and latest times of collision
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);
	std::cout << entryTime << std::endl;

	//if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) {
		normalx = 0.0f;
		normaly = 0.0f;
		//std::cout << "No Collision Detected" << std::endl;
		return 1.0f;
	}
	std::cout << "Collision Detected" << std::endl;
	//there was a collision, calculate the normal of collided surface
	if (xEntry > yEntry) {
		if (xInvEntry < 0.0f) {
			normalx = 1.0f;
			normaly = 0.0f;
		}
		else {
			normalx = -1.0f;
			normaly = 0.0f;
		}
	}
	else {
		if (yInvEntry) {
			normalx = 0.0f;
			normaly = 1.0f;
		}
		else {
			normalx = 0.0f;
			normaly = -1.0f;
		}
	}
	std::cout << "Collision Detected" << std::endl;
	return entryTime;



}*/