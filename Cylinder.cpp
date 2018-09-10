#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <sys/time.h>
#elif defined(WIN32)
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <sys/time.h>
#endif


#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"
#include "Cylinder.h"


cylinder::cylinder() {}

cylinder::cylinder(double radius, double depth, bool isSteeling, bool isRolling, double red, double green, double blue, double xPosition, double yPosition, double zPosition, double rotation)
{
	this->r = radius;
	this->d = depth;
	this->steel = isSteeling;
	this->roll = isRolling;
	this->rr = red;
	this->g = green;
	this->bb = blue;
	this->xP = xPosition;
	this->yP = yPosition;
	this->zP = zPosition;
	this->rt = rotation;


}

void cylinder::draw()
{
	static double rollspd = rollingSpeed;
	GLUquadric * quads = gluNewQuadric();

	glPushMatrix();

	glTranslated(xP, yP, zP);
	glColor3f(rr, g, bb);
	glRotated(-rt, 0, 1, 0);

	glTranslated(0, r , -d / 2);
	
	if (roll == 1)
	{
		if (checkRoll == 0)
		{
			glRotated(0, 0, 0, 1);
		}
		else if (checkRoll == 1) {
			glRotated(-rollspd/10, 0, 0, 1);
		}
		else glRotated(rollspd/10, 0, 0, 1);
	}
	gluCylinder(quads, r, r, d, 6, 1);
	gluDisk(quads, 0, r, 6, 1);

	glTranslated(0, 0, d);
	gluDisk(quads, 0, r, 6, 1);

	glPopMatrix();
	rollspd += 1;
	
}


void cylinder::checkRolling(double speed)
{
	if (speed > 0) {
		checkRoll = 1;
	}
	else if (speed < 0) {
		checkRoll = -1;
	}
	else checkRoll = 0;

}


void cylinder::setRolling(double speed)
{
	rollingSpeed = speed;
}

bool cylinder::getSteering()
{
	return steel;
}

void cylinder::setRotate(double steering)
{
	rt = steering;
}
