#pragma once
#include "Entity.h"

class GameActor : public Entity
{

protected:
	static int id_counter;
	int id;

public:
	GameActor();
	~GameActor();

	int getId() { return id; }
	virtual void moveLeft() = 0;
	virtual void moveRight() = 0;
	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
	virtual void jump() = 0;
};