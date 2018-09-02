#include "Triangular.h"
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

triangular::triangular(){}

triangular::triangular(double aLength, double bLength, double depth, double theta)
{
	this->a = aLength;
	this->b = bLength;
	this->d = depth;
	this->t = theta;
}

void triangular::draw()
{
	glBegin(GL_QUADS);
	//face ABCD
	glVertex3f(a / 2, 0, -d / 2);						//A
	glVertex3f(-a / 2, 0, -d / 2);						//B
	glVertex3f(-a / 2, 0, d / 2);						//C
	glVertex3f(a / 2, 0, d / 2);						//D
	//face BCEF
	glVertex3f(-a / 2, 0, -d / 2);						//B
	glVertex3f(-a / 2, 0, d / 2);						//C
	glVertex3f(a / 2 - b * cos(t), b * sin(t), d / 2);	//E
	glVertex3f(a / 2 - b * cos(t), b * sin(t), -d / 2);	//F
	//face ADEF
	glVertex3f(a / 2, 0, -d / 2);						//A
	glVertex3f(a / 2, 0, d / 2);						//D
	glVertex3f(a / 2 - b * cos(t), b * sin(t), d / 2);	//E
	glVertex3f(a / 2 - b * cos(t), b * sin(t), -d / 2);	//F

	glEnd();
	
	glBegin(GL_TRIANGLES);
	//face ABF
	glVertex3f(a / 2, 0, -d / 2);						//A
	glVertex3f(-a / 2, 0, -d / 2);						//B
	glVertex3f(a / 2 - b * cos(t), b * sin(t), -d / 2);	//F
	//face CDE
	glVertex3f(-a / 2, 0, d / 2);						//C
	glVertex3f(a / 2, 0, d / 2);						//D
	glVertex3f(a / 2 - b * cos(t), b * sin(t), d / 2);	//E

	glEnd();
	
}