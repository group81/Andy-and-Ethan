#include "Shape.hpp"
#include <iostream>

class cylinder : public Shape
{
private:
	double r, d, rr, g, bb, xP, yP, zP, rt;
	bool steel, roll;
	double rollingSpeed;
	int checkRoll;
public:
	cylinder();
	cylinder(double radius, double depth, bool isSteeling, bool isRolling, double red, double green, double blue, double xPosition, double yPosition, double zPosition, double rotation);
	void draw();
	void checkRolling(double speed);
	bool getSteering();
	void setRotate(double steering);
	void setRolling(double speed);
};