#pragma once
#include <memory>
#include "Sprite.h"
class Player
{
	std::unique_ptr<Sprite>
public:

	Player();
	~Player();
};

