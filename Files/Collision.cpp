#include "Collision.h"
#include "Physics.h"
#include "PlayerConstants.h"//Temporary


Collision::Collision()
{
}


Collision::~Collision()
{
}

std::unique_ptr<CollisionData> Collision::getCollisionData(const Entity &e1, const Entity &e2, int elapsed_time_ms)
{
	if (!isCollisionPossible(e1.getBox(), e2.getBox(), elapsed_time_ms))
	{
		return NULL;	//Collision is not possible
	}

	double x_pos, y_pos;
	int collision_time;
	CollisionNormal normal;





	//std::unique_ptr<CollisionData> p(new CollisionData(x_pos, y_pos, collision_time, normal));
	//return p;
}

bool Collision::isCollisionPossible(Box b1, Box b2, int elapsed_time_ms)
{
	//get broadphase boxes for b1 and b2
	Box broad1 = getBroadphaseBox(b1, elapsed_time_ms);
	Box broad2 = getBroadphaseBox(b2, elapsed_time_ms);

	//compare broad1 with broad2;
	if (broad1.x > (broad2.x + broad2.w)) {
		return false;
	}
	if ((broad1.x + broad1.w) < broad2.x) {
		return false;
	}
	if ((broad1.y + broad1.h) < broad2.y) {
		return false;
	}
	if (broad1.y > (broad2.y + broad2.h)) {
		return false;
	}

	return true;
}

Box Collision::getBroadphaseBox(Box b1, int elapsedTime)
{
	Box returnBox = Physics::actPhysicsOn(elapsedTime, MaxVelocity, b1);

	Box broad;
	if (b1.vx < 0) {
		broad.x = returnBox.x;
		broad.w = b1.x - returnBox.x + b1.w;
	}
	else {
		broad.x = b1.x;
		broad.w = returnBox.x - b1.x + b1.w;
	}

	if (b1.vy < 0) {
		broad.y = returnBox.y;
		broad.h = b1.y - returnBox.y + b1.h;
	}
	else {
		broad.y = b1.y;
		broad.h = returnBox.y - b1.y + b1.h;
	}
	return broad;
}