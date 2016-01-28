#include "Box.h"


Box::Box() : x(0), y(0), w(0), h(0), vx(0), vy(0)
{
}
Box::Box(double x_, double y_, double w_, double h_, double vx_, double vy_) : x(x_), y(y_), w(w_), h(h_), vx(vx_), vy(vy_)
{
}
void Box::print() {
	std::cout << " x: " << x << "  y: " << y << "  w: " << w << "  h: " << h << "  vx: " << vx << "  vy: " << vy << std::endl;
}

Box::~Box()
{
}
