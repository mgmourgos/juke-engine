#pragma once
#include <SDL.h>
#include <map>
#include <memory>
#include <vector>
//#include "Command.h"
#include "MoveCommand.h"

class InputHandler
{
	std::map<SDL_Keycode, bool> held_keys;
	std::map<SDL_Keycode, bool> pressed_keys;
	std::map<SDL_Keycode, bool> released_keys;
	bool leftMousePressed = false;

	std::map<SDL_Keycode, std::shared_ptr<Command>> command_map;

public:
	InputHandler();

	void beginNewFrame();

	bool getCommandsFromInput(std::vector<std::shared_ptr<Command>>& commands);

	void keyDownEvent(const SDL_Event& event);
	void keyUpEvent(const SDL_Event& event);

	bool wasKeyPressed(SDL_Keycode key);
	bool wasKeyReleased(SDL_Keycode key);
	bool isKeyHeld(SDL_Keycode key);
	bool wasLeftMousePressed();

	void mouseDownEvent(const SDL_Event& event);
};

