#include "Shape.hpp"
#include <iostream>

class rectangular : public Shape
{
private:
	double xx, yy, zz;

public:
	rectangular();
	rectangular(double x, double y, double z);
	void draw();
};
