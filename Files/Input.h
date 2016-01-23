#pragma once
#include <SDL.h>
#include <map>

class Input
{
	std::map<SDL_Keycode, bool> held_keys;
	std::map<SDL_Keycode, bool> pressed_keys;
	std::map<SDL_Keycode, bool> released_keys;
	bool leftMousePressed = false;


public:
	void beginNewFrame();

	void keyDownEvent(const SDL_Event& event);
	void keyUpEvent(const SDL_Event& event);

	bool wasKeyPressed(SDL_Keycode key);
	bool wasKeyReleased(SDL_Keycode key);
	bool isKeyHeld(SDL_Keycode key);
	bool wasLeftMousePressed();

	void mouseDownEvent(const SDL_Event& event);
};

