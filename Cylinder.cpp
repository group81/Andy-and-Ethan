#include "Cylinder.h"
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

cylinder::cylinder() {}

cylinder::cylinder(double radius, double depth)
{
	this->r = radius;
	this->d = depth;
}

void cylinder::draw()
{
	glPushMatrix();

	GLUquadric * quads = gluNewQuadric();

	glTranslated(0, 0, -d / 2);
	gluCylinder(quads, r, r, d, 15, 1);
	gluDisk(quads, 0, r, 15, 1);

	glTranslated(0, 0, d);
	gluDisk(quads, 0, r, 15, 1);

	glPopMatrix();
}