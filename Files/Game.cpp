#include "Game.h"
#include <SDL.h>
#include "Graphics.h"
#include <iostream>
#include "InputHandler.h"

namespace {
	const int FPS = 60;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);

	eventLoop();
}

Game::~Game() {
	SDL_Quit();
}

void Game::eventLoop() {

	Graphics graphics;
	InputHandler input;
	
	current_scene.reset(new Scene(graphics, 2000, 1000));

	bool running = true;
	int last_update_time = SDL_GetTicks();

	while (running) {
		const int start_time_ms = SDL_GetTicks();
		input.beginNewFrame();


		running = input.getCommandsFromInput(command_queue);

		executeCommands();

		const int current_time_ms = SDL_GetTicks();


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
	
	current_scene->executeCommands(command_queue);

	command_queue.clear();
}

void Game::draw(Graphics& graphics) {
	graphics.clear();
	current_scene->draw(graphics);
	graphics.flip();
}

void Game::update(int elapsed_time_ms) {
	current_scene->update(elapsed_time_ms);
}
