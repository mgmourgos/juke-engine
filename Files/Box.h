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
	Box();
	Box(double x_, double y_, double w_, double h_, double vx_, double vy_);
	void print();
	~Box();
};

