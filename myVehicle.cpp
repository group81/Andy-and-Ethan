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
#include "Rectangular.h"
#include "Trapezoidal.h"
#include "Triangular.h"
#include "Cylinder.h"
#include "myVehicle.h"



myVehicle::myVehicle(){}

void myVehicle::draw()
{
	glTranslated(0, 3, 0);
	rectangular rec(15, 2, 8);
	glColor3f(0, 1, 0);
	rec.draw();

	glTranslated(4, -3, 4.5);
	cylinder cyl1(2.5, 1);
	glColor3f(0, 0, 1);
	cyl1.draw();

	glTranslated(0, 0, -9);
	cylinder cyl2(2.5, 1);
	glColor3f(0, 0, 1);
	cyl2.draw();

	glTranslated(-8, 0, 0);
	cylinder cyl3(2.5, 1);
	glColor3f(0, 0, 1);
	cyl2.draw();

	glTranslated(0, 0, 9);
	cylinder cyl4(2.5, 1);
	glColor3f(0, 0, 1);
	cyl4.draw();

	glTranslated(1.5, 5, -4.5);
	rectangular rec2(10, 5, 8);
	glColor3f(1, 1, 1);
	rec2.draw();

	glTranslated(7.5, 0, 0);
	triangular tri(5, 7.071, 8, 0.7854);
	glColor3f(1, 0, 1);
	tri.draw();

	glTranslated(-5, 5, 0);
	trapezoidal tra(3, 1, 1, 5, 1);
	glColor3f(1, 1, 0);
	tra.draw();

}
