#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <SDL.h>

class Graphics;

class Sprite
{

	struct SDL_Deleter
	{
		void operator()(SDL_Window *x) const { SDL_DestroyWindow(x); }
		void operator()(SDL_Renderer *x) const { SDL_DestroyRenderer(x); }
		void operator()(SDL_Texture *x) const { SDL_DestroyTexture(x);
		std::cout << "Deleted" << std::endl;
		}
	};
	//SDL_Surface* sprite_sheet;
	//std::shared_ptr<SDL_Texture> sprite_sheet;

protected:
	SDL_Rect source_rect;

public:
	Sprite(Graphics& graphics, const std::string& file_path,
			int source_x, int source_y, int width, int height);

	void draw(Graphics& graphics, int x, int y);

	std::shared_ptr<SDL_Texture> sprite_sheet;
	
};

