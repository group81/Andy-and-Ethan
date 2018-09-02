#include "Shape.hpp"
#include <iostream>

class triangular : public Shape
{
private:
	double a, b, d, t;
public:
	triangular();
	triangular(double aLength, double bLength, double depth, double theta);
	void draw();
};