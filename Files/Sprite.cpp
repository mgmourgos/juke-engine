#include "Sprite.h"
#include <SDL.h>
#include "Graphics.h"


Sprite::Sprite(Graphics& graphics, const std::string& file_path,
	int source_x, int source_y, int width, int height) {

	//sprite_sheet = graphics.loadImage(file_path);
	source_rect.x = source_x;
	source_rect.y = source_y;
	source_rect.w = width;
	source_rect.h = height;
}


void Sprite::draw(Graphics& graphics, int x, int y) {

	SDL_Rect destination_rectangle;
	destination_rectangle.x = x;
	destination_rectangle.y = y;
	//graphics.blitSurface(sprite_sheet, &source_rect, &destination_rectangle);
}
