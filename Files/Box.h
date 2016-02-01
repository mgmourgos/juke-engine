#pragma once
#include <iostream>
class Box
{

public:
	// position of top-left corner
	double x, y;

	// dimensions
	double w, h;

	// velocity
	double vx, vy;

	// acceleration
	double ax, ay;
	Box();
	Box(double x_, double y_, double w_, double h_, double vx_, double vy_);
	Box(double x_, double y_, double w_, double h_, double vx_, double vy_, double ax_, double ay_);
	void print();
	~Box();
};

