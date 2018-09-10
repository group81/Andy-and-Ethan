#include "Shape.hpp"
#include <iostream>

class rectangular : public Shape
{
private:
	double xx, yy, zz, r, g, b, xP, yP, zP;

public:
	rectangular();
	rectangular(double x, double y, double z, double red, double green, double blue, double xPosition, double yPosition, double zPosition);
	void draw();
};
