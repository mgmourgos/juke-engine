#include "Graphics.h"
#include <iostream>
#include "GameConstants.h"

Graphics::Graphics()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {																	//if initialization failed
		std::cout << "SDL could not be initialized. Error: " << SDL_GetError() << std::endl;
	}
	else {
		mainWindow.reset(SDL_CreateWindow("Juke", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
						 SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
		if (!mainWindow) {																						//if window does not own anything
			std::cout << "Window could not be created. Error: " << SDL_GetError() << std::endl;
		}

		mainRenderer.reset(SDL_CreateRenderer(mainWindow.get(), -1, SDL_RENDERER_ACCELERATED));

	}
}


Graphics::~Graphics()
{
}

std::shared_ptr<SDL_Texture> Graphics::loadImage(const std::string& file_path) {

	if (sprite_sheets.count(file_path) == 0) {											//if sprite sheet is not already loaded
		SDL_Surface* tempSurface = SDL_LoadBMP(file_path.c_str());						//create shared_ptr that points to .bmp
																						
		if (tempSurface == NULL) {													
			std::cout << ".bmp could not be loaded" << std::endl;
			return NULL;
		}

		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 100, 200, 50));

		SDL_Texture* texture = SDL_CreateTextureFromSurface(mainRenderer.get(), tempSurface);

		sprite_sheets[file_path].reset(texture, SDL_Deleter());

		SDL_FreeSurface(tempSurface);
	}

	return sprite_sheets[file_path];													
}


void Graphics::draw(SDL_Texture* ptr_, SDL_Rect source_rect, SDL_Rect dest_rect) const {
	SDL_RenderCopy(mainRenderer.get(), ptr_, &source_rect, &dest_rect);
}

void Graphics::clear() {
	SDL_RenderClear(mainRenderer.get());
}

void Graphics::flip() {
	SDL_RenderPresent(mainRenderer.get());
}