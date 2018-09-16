#include "Shape.hpp"
#include <iostream>

class triangular : public Shape
{
private:
	double a, b, d, t, r, g, bb, xP, yP, zP, rt;
public:
	triangular();
	triangular(double aLength, double bLength, double depth, double theta, double red, double green, double blue, double xPosition, double yPosition, double zPosition, double rotation);
	void draw();
};