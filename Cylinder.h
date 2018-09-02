#include "Shape.hpp"
#include <iostream>

class cylinder : public Shape
{
private:
	double r, d;
public:
	cylinder();
	cylinder(double radius, double depth);
	void draw();

};