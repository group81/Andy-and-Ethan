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

cylinder::cylinder(double radius, double depth, bool isSteeling, bool isRolling, double red, double green, double blue, double xPosition, double yPosition, double zPosition)
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
}

void cylinder::draw()
{
	GLUquadric * quads = gluNewQuadric();

	glPushMatrix();

	glTranslated(xP, yP, zP);
	glColor3f(rr, g, bb);
	glRotated(-rt, 0, 1, 0);

	glTranslated(0, r , -d / 2);

	gluCylinder(quads, r, r, d, 6, 1);
	gluDisk(quads, 0, r, 6, 1);

	glTranslated(0, 0, d);
	gluDisk(quads, 0, r, 6, 1);

	glPopMatrix();
}
