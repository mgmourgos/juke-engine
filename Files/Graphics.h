#pragma once
#include <map>
#include <memory>
#include <SDL.h>

class Graphics
{
	struct SDL_Deleter
	{
		void operator()(SDL_Window *x) const { SDL_DestroyWindow(x); }
		void operator()(SDL_Renderer *x) const { SDL_DestroyRenderer(x); }
		void operator()(SDL_Texture *x) const { SDL_DestroyTexture(x); }
	};

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

