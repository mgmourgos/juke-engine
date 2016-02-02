#include "Collision.h"
#include "Physics.h"
#include "PlayerConstants.h"//Temporary


Collision::Collision()
{
}


Collision::~Collision()
{
}

std::unique_ptr<CollisionData> Collision::getCollisionData(const Entity& e1, const Entity& e2, int elapsed_time_ms)
{
	
	Box b1, b2;
	b1 = e1.getBox();
	b2 = e2.getBox();

	if (!isCollisionPossible(b1, b2, elapsed_time_ms))
	{
		return nullptr;	//Collision is not possible
	}
	

	double x_pos, y_pos;
	double x_vel_obj, y_vel_obj;
	//int collision_time;
	CollisionNormal normal;
	CollisionType type;

	Box combined_vel_box;
	combined_vel_box = b1;

	combined_vel_box.vx = b1.vx - b2.vx;
	combined_vel_box.vy = b1.vy - b2.vy;

	//~~~~~~~~~~~~~~~~~~~~~Finding locational state~~~~~~~~~~~~~~~~~~~~~~

	bool s1, s2, s3, s4;
	s1 = s2 = s3 = s4 = false;


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
	if (combined_vel_box.x > (b2.x + b2.w)) {//then b1 is to the right of b2		in state 4
		//then no collision
		s4 = true;
	}
	else
	if ((combined_vel_box.x + combined_vel_box.w) < b2.x) {//then b1 is to the left of b2		in state 2
		s2 = true;
	}

	if ((combined_vel_box.y + combined_vel_box.h) < b2.y) {//then b1 is above b2				in state 1
		s1 = true;
	}
	else
	if (combined_vel_box.y > (b2.y + b2.h)) {//then b1 is below b2				in state 3
		s3 = true;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (s1)//if b1 above b2
	{
		
		//1 set b1new.y = b2.y - b1.h - .01f;
		//2 find elapsed time to go from b1.y to b1new.y using b1.vy		AND b1.ay????
		//3 set b1new.x = b1new.vx * elapsed using
		//4  if boxes collide on x axis
			//then collision HAS occured
			//then normal is BOTTOM
			//then elapsed time = elapsed time
			//then colision x and y position = elapsed_time * b1.vx and b1.vy 
		Box collision_check_box;
		double deltay;
		int collision_time;
		collision_check_box = combined_vel_box;
		collision_check_box.y = b2.y - b1.h;// -0.01f;//1
		deltay = collision_check_box.y - b1.y;
		std::cout << "combined_vel_box.y:" << combined_vel_box.y << std::endl;
		std::cout << "combined_vel_box.vy:" << combined_vel_box.vy << std::endl;

		collision_time = deltay / combined_vel_box.vy;//2
		if (collision_time < elapsed_time_ms)
		{

			collision_check_box.x += combined_vel_box.vx * collision_time;//3
			if (doesXAxisCollide(collision_check_box, b2))//4
			{
				x_pos = b1.x + b1.vx * collision_time;
				y_pos = b1.y + b1.vy * (double)collision_time;
				x_vel_obj = b2.vx;
				y_vel_obj = b2.vy;
				normal = BOTTOM;
				type = e1.getCollisionType();
				std::unique_ptr<CollisionData> p(new CollisionData(x_pos, y_pos, x_vel_obj, y_vel_obj, collision_time, normal, type));
				return p;
			}
		}
	}
	if (s2)
	{
		
	}
	if (s3)
	{
		
	}
	if (s4)
	{
		
	}
	return nullptr;





	//std::unique_ptr<CollisionData> p(new CollisionData(x_pos, y_pos, collision_time, normal));
	//return p;
	
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
	if ((b1.y + b1.h) < b2.y)
	{
		return false; //b1 above b2
	}
	if (b1.y > (b2.y + b2.h))
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