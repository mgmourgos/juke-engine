#pragma once

class Player;

class PlayerState 
{


public:
	PlayerState();
	~PlayerState();

	virtual void handleInput(Player& player/*, Input input*/) {}
};