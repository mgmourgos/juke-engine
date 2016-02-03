#include "Game.h"
#include <SDL.h>
#include <math.h>
#include "Graphics.h"
#include "Sprite.h"
#include <iostream>
#include "InputHandler.h"
#include "EnvironmentEntity.h"
#include "Physics.h"//GET RID OF THIS WHEN COLLISION IS MOVED
#include "PlayerConstants.h"//GET RID OF THIS WHEN COLLISION IS MOVED
#include "Collision.h"//GET RID OF THIS WHEN COLLISION IS MOVED?
#include "CollisionData.h"

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
	
	Sprite BackGround(graphics, "Files/Background.bmp", 0, 0, 640, 480);

	std::shared_ptr<Player> player = std::make_shared<Player>(graphics, 320, 240);
	entity_queue.push_back(player);
	gameActor_queue.push_back(player);

	
	//std::shared_ptr<EnvironmentEntity> platform = std::make_shared<EnvironmentEntity>(graphics, 350, 350, 50, 20);
	/*
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 400, 240, 100, 20);


	entity_queue.push_back(platform);//All game objects are in the entity queue
									//All gameActors are in gameActor_queue
	platform = std::make_shared<EnvironmentEntity>(graphics,35, 450, 500, 400);
	entity_queue.push_back(platform);

	platform = std::make_shared<EnvironmentEntity>(graphics, 0, 100, 50, 400);
	entity_queue.push_back(platform);

	//short blocks for walking~~~~~~~~~~~~~~~ 
	
	platform = std::make_shared<EnvironmentEntity>(graphics, 140, 400, 20, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 160, 400, 20, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 180, 400, 20, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 200, 400, 20, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 220, 400, 20, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 240, 400, 20, 10);
	entity_queue.push_back(platform);

	platform = std::make_shared<EnvironmentEntity>(graphics, 105, 375, 1, 20);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 105, 362, 1, 10);
	entity_queue.push_back(platform);

	*/
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::shared_ptr<EnvironmentEntity> platform = std::make_shared<EnvironmentEntity>(graphics, 10, 300, 600, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 10, 150, 600, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 20, 120, 10, 300);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 590, 120, 10, 300);
	entity_queue.push_back(platform);

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
	//list of collisions for each entity is set
	for (auto &entity1 : entity_queue) {
		//if (entity1->getCollisionType() != UNMOVABLE) {
			for (auto &entity2 : entity_queue) {
				if (entity1 != entity2) {
					//checkCollision(entity1, entity2);
					std::unique_ptr<CollisionData> data;
					data = Collision::getCollisionData(*entity1, *entity2, elapsed_time_ms);
					if (data != nullptr)
					{
						entity1->addCollision(std::move(data));
					}
				}
			}
		//}
	}

	//call update on each entity
	for (auto &entity : entity_queue) {
		entity->update(elapsed_time_ms);
	}
}
