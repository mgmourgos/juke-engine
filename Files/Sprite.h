#pragma once

#include <string>
#include <SDL.h>

class Graphics;

class Sprite
{
	SDL_Surface* sprite_sheet;

protected:
	SDL_Rect source_rect;

public:
	Sprite(Graphics& graphics, const std::string& file_path,
			int source_x, int source_y, int width, int height);

	void draw(Graphics& graphics, int x, int y);
	
};

