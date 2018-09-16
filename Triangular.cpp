#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Shape.hpp"
#include "Vehicle.hpp"
#include "Triangular.h"

triangular::triangular(){}

triangular::triangular(double aLength, double bLength, double depth, double theta, double red, double green, double blue, double xPosition, double yPosition, double zPosition, double rotation)
{
	this->a = aLength;
	this->b = bLength;
	this->d = depth;
	this->t = theta*3.1415926/180;
	this->r = red;
	this->g = green;
	this->bb = blue;
	this->xP = xPosition;
	this->yP = yPosition;
	this->zP = zPosition;
	this->rt = rotation;
}

void triangular::draw()
{
	glPushMatrix();
	glTranslated(xP, yP, zP);
	glColor3f(r, g, bb);
	glRotated(rt, 0, 1, 0);

	glBegin(GL_QUADS);
	//face ABCD
	glVertex3f(-a / 2, 0, -d / 2);						//A
	glVertex3f(a / 2, 0, -d / 2);						//B
	glVertex3f(a / 2, 0, d / 2);						//C
	glVertex3f(-a / 2, 0, d / 2);						//D
														//face BCEF
	glVertex3f(a / 2, 0, -d / 2);						//B
	glVertex3f(a / 2, 0, d / 2);						//C
	glVertex3f(-a / 2 + b * cos(t), b * sin(t), d / 2);	//E
	glVertex3f(-a / 2 + b * cos(t), b * sin(t), -d / 2);	//F
														//face ADEF
	glVertex3f(-a / 2, 0, -d / 2);						//A
	glVertex3f(-a / 2, 0, d / 2);						//D
	glVertex3f(-a / 2 + b * cos(t), b * sin(t), d / 2);	//E
	glVertex3f(-a / 2 + b * cos(t), b * sin(t), -d / 2);	//F

	glEnd();

	glBegin(GL_TRIANGLES);
	//face ABF
	glVertex3f(-a / 2, 0, -d / 2);						//A
	glVertex3f(a / 2, 0, -d / 2);						//B
	glVertex3f(-a / 2 + b * cos(t), b * sin(t), -d / 2);	//F
														//face CDE
	glVertex3f(a / 2, 0, d / 2);						//C
	glVertex3f(-a / 2, 0, d / 2);						//D
	glVertex3f(-a / 2 + b * cos(t), b * sin(t), d / 2);	//E

	glEnd();

	glPopMatrix();
}