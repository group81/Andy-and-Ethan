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



myVehicle::myVehicle()
{
	//implement the how to convert local vehicle into structure for uploading to the server
}

myVehicle::myVehicle(VehicleModel remote)
{
	//How to convert the remote vehicle downloading from the server
}


void myVehicle::draw()
{
	//Draw local and remote car
}

void myVehicle::myVehicleModel()
{

	ShapeInit c6;
	c6.xyz[0] = 0;
	c6.xyz[1] = 0;
	c6.xyz[2] = 0;
	c6.rgb[0] = 1;
	c6.rgb[1] = 0;
	c6.rgb[2] = 0;
	c6.params.cyl.depth = 3;
	c6.params.cyl.radius = 4;
	c6.params.cyl.isRolling = 1;
	c6.params.cyl.isSteering = 1;
	c6.type = CYLINDER;
	c6.rotation = 0;
	local.shapes.push_back(c6);
	
	ShapeInit tra;
	tra.xyz[0] = 0;
	tra.xyz[1] = 6;
	tra.xyz[2] = 0;
	tra.rgb[0] = 0;
	tra.rgb[1] = 1;
	tra.rgb[2] = 0;
	tra.params.trap.alen = 10;
	tra.params.trap.blen = 8;
	tra.params.trap.aoff = 1;
	tra.params.trap.depth = 5;
	tra.params.trap.height = 5;
	tra.type = TRAPEZOIDAL_PRISM;
	tra.rotation = 0;
	local.shapes.push_back(tra);



}

VehicleModel myVehicle::setLocal()
{
	return local;
}