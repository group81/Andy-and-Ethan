
#ifndef MTRN3500_OBSTACLE_H
#define MTRN3500_OBSTACLE_H

#include "Shape.hpp"


class Obstacle : public Shape {

private:
	double radius;

public:
	Obstacle(double x_, double z_, double radius_);
	void draw();
	bool equals(Obstacle & other);

	double getRadius();
};

#endif // for MTRN3500_OBSTACLE_H

