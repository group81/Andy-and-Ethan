#include "Rectangular.h"
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

rectangular::rectangular(){}

rectangular::rectangular(double x, double y, double z, double red, double green, double blue, double xPosition, double yPosition, double zPosition) {
	this->xx = x;
	this->yy = y;
	this->zz = z;
	this->r = red;
	this->g = green;
	this->b = blue;
	this->xP = xPosition;
	this->yP = yPosition;
	this->zP = zPosition;
}

void rectangular::draw() {

	glPushMatrix();
	glTranslated(xP, yP, zP);
	glColor3f(r, g, b);

	glBegin(GL_QUADS);
	//face ABCD
	glVertex3f(xx / 2, 0, -zz / 2);			//A
	glVertex3f(-xx / 2, 0, -zz / 2);		//B
	glVertex3f(-xx / 2, 0, zz / 2);			//C
	glVertex3f(xx / 2, 0, zz / 2);			//D
	//face EFHG
	glVertex3f(xx / 2, yy, -zz / 2);		//E
	glVertex3f(-xx / 2, yy, -zz / 2);		//F
	glVertex3f(-xx / 2, yy, zz / 2);		//G
	glVertex3f(xx / 2, yy, zz / 2);			//H
	//face ABFE
	glVertex3f(xx / 2, 0, -zz / 2);			//A
	glVertex3f(-xx / 2, 0, -zz / 2);		//B
	glVertex3f(-xx / 2, yy, -zz / 2);		//F
	glVertex3f(xx / 2, yy, -zz / 2);		//E
	//BCGF
	glVertex3f(-xx / 2, 0, -zz / 2);		//B
	glVertex3f(-xx / 2, 0, zz / 2);			//C
	glVertex3f(-xx / 2, yy, zz / 2);		//G
	glVertex3f(-xx / 2, yy, -zz / 2);		//F
	//CDHG
	glVertex3f(-xx / 2, 0, zz / 2);			//C
	glVertex3f(xx / 2, 0, zz / 2);			//D
	glVertex3f(xx / 2, yy, zz / 2);			//H
	glVertex3f(-xx / 2, yy, zz / 2);		//G
	//DAEH
	glVertex3f(xx / 2, 0, zz / 2);			//D
	glVertex3f(xx / 2, 0, -zz / 2);			//A
	glVertex3f(xx / 2, yy, -zz / 2);		//E
	glVertex3f(xx / 2, yy, zz / 2);			//H
	glEnd();

	glPopMatrix();

}
