#include "Shape.hpp"
#include <iostream>

class cylinder : public Shape
{
private:
	double r, d, rr, g, bb, xP, yP, zP;
	bool steel, roll;
public:
	cylinder();
	cylinder(double radius, double depth, bool isSteeling, bool isRolling, double red, double green, double blue, double xPosition, double yPosition, double zPosition);
	void draw();
}