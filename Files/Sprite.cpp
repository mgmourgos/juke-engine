#include "Sprite.h"
#include <SDL.h>
#include "Graphics.h"
#include <iostream>


Sprite::Sprite(Graphics& graphics, const std::string& file_path,
	int source_x, int source_y, int width, int height) {

	sprite_sheet.reset(graphics.loadImage(file_path).get(), SDL_Deleter());

	std::cout << "sprite_sheet add: " << sprite_sheet.get() << std::endl;
	if (!sprite_sheet) {
		std::cout << "ptr is not a valid pointer.\n" << std::endl;
	}
	source_rect.x = source_x;
	source_rect.y = source_y;
	source_rect.w = width;
	source_rect.h = height;
}


void Sprite::draw(Graphics& graphics, int x, int y) {

	SDL_Rect destination_rectangle;
	destination_rectangle.x = x;
	destination_rectangle.y = y;
	destination_rectangle.w = source_rect.w;
	destination_rectangle.h = source_rect.h;
	//graphics.blitSurface(sprite_sheet, &source_rect, &destination_rectangle);
	graphics.draw(sprite_sheet.get(), source_rect, destination_rectangle);
}
