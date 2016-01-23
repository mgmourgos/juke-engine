#include "Game.h"
#include <SDL.h>
#include <math.h>
#include "Graphics.h"
#include "Sprite.h"
#include <iostream>
#include "Input.h"


namespace {
	const int FPS = 60;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	player = new Player(graphics, 320, 240);
	eventLoop();
	
	AllSprites.clear();
}

Game::~Game() {
	delete player;
	SDL_Quit();
}

void Game::eventLoop() {

	SDL_Event event;
	//Graphics graphics;
	Input input;
	
	//Sprite BackGround(graphics, "Files/Background.bmp", 0, 0, 640, 400);
	//graphics.loadImage("Files/Background.bmp");

	
	Sprite BackGround(graphics, "Files/Background.bmp", 0, 0, 640, 480);
	std::cout << "game sprite address: " << BackGround.sprite_sheet.get() << std::endl;
	AllSprites.push_back(BackGround);
	
	//update(0);
	
	
	bool running = true;
	int last_update_time = SDL_GetTicks();

	while (running) {
		const int start_time_ms = SDL_GetTicks();
		input.beginNewFrame();
		while (SDL_PollEvent(&event)) {
		
			switch (event.type) {
				case SDL_KEYDOWN:
					input.keyDownEvent(event);
					break;
				case SDL_KEYUP:
					input.keyUpEvent(event);
					break;
				case SDL_MOUSEBUTTONDOWN:
					input.mouseDownEvent(event);
					break;
				case SDL_QUIT:
					running = false;
					break;
				default:
					break;
			}
		}
		
		if (input.wasKeyPressed(SDLK_ESCAPE)) {
			running = false;
		}

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

void Game::draw(Graphics& graphics_) {
	graphics.clear();
	for (int i = 0; i < AllSprites.size(); i++) {
		AllSprites[i].draw(graphics, 0, 0);
	}
	player->draw(graphics);
	graphics.flip();
}

void Game::update(int elapsed_time_ms) {



}
