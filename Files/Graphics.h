#pragma once
#include <map>
#include <memory>
#include <SDL.h>
#include "SDL_Deleter.h"

class Graphics
{
	typedef std::map<std::string, std::shared_ptr<SDL_Texture>> TextureMap;
	TextureMap sprite_sheets;

	std::unique_ptr<SDL_Window, SDL_Deleter> mainWindow;
	std::unique_ptr<SDL_Texture, SDL_Deleter> backgroundTx;
	std::unique_ptr<SDL_Renderer, SDL_Deleter> mainRenderer;

public:
	Graphics();
	~Graphics();

	void clear();
	void flip();
	void draw(SDL_Texture* ptr, SDL_Rect source_rect, SDL_Rect dest_rect);

	std::shared_ptr<SDL_Texture> loadImage(const std::string& file_path);
};

