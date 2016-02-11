#include "Collision.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}

std::unique_ptr<CollisionData> Collision::getCollisionData(const Entity& entity_1, const Entity& entity_2, int elapsed_time_ms)
{
	
	Box b1, b2;
	b1 = entity_1.getBox();
	b2 = entity_2.getBox();

	if (!isCollisionPossible(b1, b2, elapsed_time_ms))
	{
		return nullptr;	//Collision is not possible
	}

	//~~~~~~~~~~~~~~~~~~~~~Finding locational state~~~~~~~~~~~~~~~~~~~~~~

	bool is_b1_above_b2, is_b1_left_of_b2, is_b1_below_b2, is_b1_right_of_b2;

	is_b1_above_b2 = is_b1_left_of_b2 = is_b1_below_b2 = is_b1_right_of_b2 = false; //still n00bz...

	/*		State Diagram:

	1	 |1 |	1
	2	 |  |	4
	-----~~~~-----
	2	 |b2|   4
	-----~~~~-----
	2	 |  |	4
	3	 | 3|	3
	*/

	//checks which side of b2 b1 is on.
	if (b1.x > (b2.x + b2.w)) {
		is_b1_right_of_b2 = true;
	}
	else
		if ((b1.x + b1.w) < b2.x) {
		is_b1_left_of_b2 = true;
	}

	if ((b1.y - b1.h) > b2.y) {			
		is_b1_above_b2 = true;
	}
	else
		if (b1.y < (b2.y - b2.h)) {			
		is_b1_below_b2 = true;
	}


	//~~~~~~~~~~~~~~~~~~~~~~handling collision if there is any~~~~~~~~~~~~~~~~~~~~~~~~~

	CollisionType entity2_collision_type = entity_2.getCollisionType();

	if (is_b1_above_b2)//if b1 above b2
	{
		std::unique_ptr<CollisionData> p_collision_data = determineCollisionData(BOTTOM, b1, b2, entity2_collision_type, elapsed_time_ms);
		return p_collision_data;
	}
	if (is_b1_left_of_b2)
	{
		std::unique_ptr<CollisionData> p_collision_data = determineCollisionData(RIGHT, b1, b2, entity2_collision_type, elapsed_time_ms);

		return p_collision_data;
	}
	if (is_b1_below_b2)
	{
		std::unique_ptr<CollisionData> p_collision_data = determineCollisionData(TOP, b1, b2, entity2_collision_type, elapsed_time_ms);
		return p_collision_data;
	}
	if (is_b1_right_of_b2)
	{
		std::unique_ptr<CollisionData> p_collision_data = determineCollisionData(LEFT, b1, b2, entity2_collision_type, elapsed_time_ms);
		return p_collision_data;
	}
	return nullptr;
	
}

std::unique_ptr<CollisionData> Collision::determineCollisionData(CollisionNormal normal, Box b1, Box b2, CollisionType entity_2_collision_type, int elapsed_time_ms)
{
	Box combined_vel_box;
	combined_vel_box = b1;

	combined_vel_box.vx = b1.vx - b2.vx;
	combined_vel_box.vy = b1.vy - b2.vy;

	double x_vel_obj, y_vel_obj;

	double delta;
	double collision_time;

	bool collision_occurs = false;

	Box collision_check_box;
	collision_check_box = combined_vel_box;

	switch(normal) {
	
		case BOTTOM: 
			collision_check_box.y = b2.y + b1.h;
			delta = collision_check_box.y - b1.y;
			break;
		case TOP:
			collision_check_box.y = b2.y - b2.h;
			delta = b1.y - collision_check_box.y;
			break;
		case LEFT:
			collision_check_box.x = b2.x + b2.w;
			delta = collision_check_box.x - b1.x;
			break;
		case RIGHT:
			collision_check_box.x = b2.x - b1.w;
			delta = b1.x - collision_check_box.x;
			break;
	};

	if (normal == TOP || normal == BOTTOM)
	{
		collision_time = fabs(delta / combined_vel_box.vy);
		if (normal == BOTTOM && combined_vel_box.vy > 0)
		{
			//return no collision because distance between b1 and b2 is increasing
			return nullptr;
		}
		
		collision_check_box.x += combined_vel_box.vx * collision_time;
		collision_occurs = doesXAxisCollide(collision_check_box, b2);

	}
	else if (normal == LEFT || normal == RIGHT)
	{
		collision_time = fabs(delta / combined_vel_box.vx);
		collision_check_box.y += combined_vel_box.vy * collision_time;
		collision_occurs = doesYAxisCollide(collision_check_box, b2);

	}


	//Collision definitely occurs
	if (collision_time < elapsed_time_ms && collision_occurs)
	{
			x_vel_obj = b2.vx;
			y_vel_obj = b2.vy;
			std::unique_ptr<CollisionData> p(new CollisionData(x_vel_obj, y_vel_obj, collision_time, normal, entity_2_collision_type));
			return p;
	}

	return nullptr;

}

bool Collision::doesXAxisCollide(Box b1, Box b2)
{
	//Checks whether or not b1 and b2 overlap when projected onto the X axis
	if ((b1.x + b1.w) < b2.x)
	{
		return false; //b1 to left of b2
	}
	if (b1.x > (b2.x + b2.w))
	{
		return false; //b1 to right of b2
	}
	return true; //else b1 is overlapping b2 on x axis

}
bool Collision::doesYAxisCollide(Box b1, Box b2)
{
	//Checks whether or not b1 and b2 overlap when projected onto the Y axis
	if ((b1.y - b1.h) > b2.y)
	{
		return false; //b1 above b2
	}
	if (b1.y < (b2.y - b2.h))
	{
		return false; //b1 below b2
	}
	return true; //else b1 is overlapping b2 on y axis
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
	if ((broad1.y - broad1.h) > broad2.y) {
		return false;
	}
	if (broad1.y < (broad2.y - broad2.h)) {
		return false;
	}

	return true;
}

Box Collision::getBroadphaseBox(Box b1, int elapsed_time_ms)
{
	Box returnBox = getUpdatedPosition(b1, elapsed_time_ms);

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
		broad.y = b1.y;
		broad.h = b1.y - returnBox.y + b1.h;
	}
	else {
		broad.y = returnBox.y;
		broad.h = returnBox.y - b1.y + b1.h;
	}
	return broad;
}

Box Collision::getUpdatedPosition(Box b1, int elapsed_time_ms)
{
	b1.x += b1.vx * elapsed_time_ms;
	b1.y += b1.vy * elapsed_time_ms;

	return b1;
}