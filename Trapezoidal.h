#include "Shape.hpp"
#include <iostream>

class trapezoidal : public Shape
{
private:
	double a, b, h, d, o;
public:
	trapezoidal();
	trapezoidal(double aLength, double bLength, double height, double depth, double offset);
	void draw();
};