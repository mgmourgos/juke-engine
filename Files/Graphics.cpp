#include "Graphics.h"
//#include <SDL.h>
#include <iostream>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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

		SDL_Texture* texture = SDL_CreateTextureFromSurface(mainRenderer.get(), tempSurface);
		std::cout << "text add: " << texture << std::endl;

		sprite_sheets[file_path].reset(texture, SDL_Deleter());

		SDL_FreeSurface(tempSurface);
	}
	//std::cout << "text add: " << &texture << std::endl;

	return sprite_sheets[file_path];													
}


void Graphics::draw(SDL_Texture* ptr_, SDL_Rect source_rect, SDL_Rect dest_rect) {
	//std::cout << "Trying to draw to renderer" << std::endl;
	SDL_RenderCopy(mainRenderer.get(), ptr_, &source_rect, &dest_rect);
	//SDL_RenderPresent(mainRenderer.get());
}

void Graphics::clear() {
	SDL_RenderClear(mainRenderer.get());
}

void Graphics::flip() {
	//std::cout << "Trying to present to screen" << std::endl;

	/*
	SDL_Surface* loadingSurf = SDL_LoadBMP("Files/Background.bmp");
	SDL_Texture* backgroundTx = SDL_CreateTextureFromSurface(mainRenderer.get(), loadingSurf);
	SDL_FreeSurface(loadingSurf);

	SDL_RenderCopy(mainRenderer.get(), backgroundTx, NULL, NULL);//adds the background to the renderer screen
	SDL_DestroyTexture(backgroundTx);
	*/







	SDL_RenderPresent(mainRenderer.get());
}