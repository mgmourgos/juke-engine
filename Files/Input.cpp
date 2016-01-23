#include "Input.h"


void Input::beginNewFrame() {
	pressed_keys.clear();
	released_keys.clear();
	leftMousePressed = false;
}

void Input::keyDownEvent(const SDL_Event& event) {
	pressed_keys[event.key.keysym.sym] = true;
	held_keys[event.key.keysym.sym] = true;
}

void Input::keyUpEvent(const SDL_Event& event) {
	released_keys[event.key.keysym.sym] = true;
	held_keys[event.key.keysym.sym] = false;
}

bool Input::wasKeyPressed(SDL_Keycode key) {
	return pressed_keys[key];
}

bool Input::wasKeyReleased(SDL_Keycode key) {
	return released_keys[key];
}

bool Input::isKeyHeld(SDL_Keycode key) {
	return held_keys[key];
}

void Input::mouseDownEvent(const SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		leftMousePressed = true;
	}
}

bool Input::wasLeftMousePressed() {
	return leftMousePressed;
}
