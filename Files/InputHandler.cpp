#include "InputHandler.h"
#include <iostream>


bool InputHandler::getCommandsFromInput(std::vector<std::shared_ptr<Command>>& command_queue) {
	
	//Polls all events in frame and handles key maps
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				return false;
			}
			keyDownEvent(event);
		}
		else if (event.type == SDL_KEYUP) {
			keyUpEvent(event);
		}
	}

	//Iterates through held keys, checks if held/pressed/released keys warrant command
	//pushes commands to command_queue
	std::map<SDL_Keycode, bool>::iterator iter;
	for (iter = held_keys.begin(); iter != held_keys.end(); iter++) {
		if (command_map[iter->first] != 0 && iter->second == true) {
			if (command_map[iter->first]->getActivationType() == Command::ONHELD ||
			   (command_map[iter->first]->getActivationType() == Command::ONPRESS &&
				wasKeyPressed(iter->first))) {
					command_queue.push_back(command_map[iter->first]);
			}
		}
	}

	return true;
}

//initializes command_map
//This is where we change which key links to a certain command
InputHandler::InputHandler() {
	command_map[SDLK_LEFT] = std::make_shared<MoveLeftCommand>();
	command_map[SDLK_RIGHT] = std::make_shared<MoveRightCommand>();
	command_map[SDLK_UP] = std::make_shared<MoveUpCommand>();
	command_map[SDLK_DOWN] = std::make_shared<MoveDownCommand>();
}

void InputHandler::beginNewFrame() {
	pressed_keys.clear();
	released_keys.clear();
	leftMousePressed = false;
}

void InputHandler::keyDownEvent(const SDL_Event& event) {
	pressed_keys[event.key.keysym.sym] = true;
	held_keys[event.key.keysym.sym] = true;
}

void InputHandler::keyUpEvent(const SDL_Event& event) {
	released_keys[event.key.keysym.sym] = true;
	held_keys[event.key.keysym.sym] = false;
}

bool InputHandler::wasKeyPressed(SDL_Keycode key) {
	return pressed_keys[key];
}

bool InputHandler::wasKeyReleased(SDL_Keycode key) {
	return released_keys[key];
}

bool InputHandler::isKeyHeld(SDL_Keycode key) {
	return held_keys[key];
}

void InputHandler::mouseDownEvent(const SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		leftMousePressed = true;
	}
}

bool InputHandler::wasLeftMousePressed() {
	return leftMousePressed;
}
