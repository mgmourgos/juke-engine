#include "GameActor.h"

int GameActor::id_counter = 0;

GameActor::GameActor() : jumping(true)
{
	id = id_counter++;
}

GameActor::~GameActor() {

}