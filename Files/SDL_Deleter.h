#pragma once
#include <SDL.h>

class SDL_Deleter
{

public:

	void operator()(SDL_Window *x) const { SDL_DestroyWindow(x); }
	void operator()(SDL_Renderer *x) const { SDL_DestroyRenderer(x); }
	void operator()(SDL_Texture *x) const { SDL_DestroyTexture(x); }

};