#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <SDL.h>
#include "SDL_Deleter.h"

class Graphics;

class Sprite
{

protected:
	SDL_Rect source_rect;

public:
	Sprite(Graphics& graphics, const std::string& file_path,
			int source_x, int source_y, int width, int height);

	void draw(const Graphics& graphics, int x, int y) const;

	std::shared_ptr<SDL_Texture> sprite_sheet;
	
};

