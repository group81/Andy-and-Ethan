#include "Shape.hpp"
#include <iostream>

class trapezoidal : public Shape
{
private:
	double a, b, h, d, o, r, g, bb, xP, yP, zP, rt;
public:
	trapezoidal();
	trapezoidal(double aLength, double bLength, double height, double depth, double offset, double red, double green, double blue, double xPosition, double yPosition, double zPosition);
	void draw();
};