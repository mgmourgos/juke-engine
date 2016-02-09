#include "InputHandler.h"
#include "PushCommand.h"
#include <iostream>


bool InputHandler::getCommandsFromInput(std::vector<std::shared_ptr<Command>>& command_queue) {
	
	//Pulls all events in frame and handles key map
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				return false;
			}
			if (event.key.repeat == 0) { //then key is not a repeat...?
				keyDownEvent(event);
			}
		}
		else if (event.type == SDL_KEYUP) {
			keyUpEvent(event);
		}
	}
	
	//Iterates through held keys, checks if held/pressed/released keys warrant a command
	//Pushes commnands to command queue
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

InputHandler::InputHandler() {

	command_map[SDLK_LEFT] = std::make_shared<MoveLeftCommand>();
	command_map[SDLK_RIGHT] = std::make_shared<MoveRightCommand>();
	command_map[SDLK_UP] = std::make_shared<JumpCommand>();
	command_map[SDLK_LSHIFT] = std::make_shared<PushCommand>();
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
