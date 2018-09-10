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
	myVehicleModel();
	for (std::vector<ShapeInit>::iterator it = local.shapes.begin(); it != local.shapes.end(); ++it)
	{
		if (it->type == RECTANGULAR_PRISM)
		{
			rectangular* rec = NULL;
			rec = new rectangular(it->params.rect.xlen, it->params.rect.ylen, it->params.rect.zlen, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2]);
			addShape(rec);
		}

		else if (it->type == TRIANGULAR_PRISM)
		{
			triangular * tri = NULL;
			tri = new triangular(it->params.tri.alen, it->params.tri.blen, it->params.tri.depth, it->params.tri.angle, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2]);
			addShape(tri);
		}

		else if (it->type == TRAPEZOIDAL_PRISM)
		{
			trapezoidal * tra = NULL;
			tra = new trapezoidal(it->params.trap.alen, it->params.trap.blen, it->params.trap.height, it->params.trap.depth, it->params.trap.aoff, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2], it->rotation);
			addShape(tra);
		}

		else if (it->type == CYLINDER)
		{
			cylinder * cyl = NULL;
			cyl = new cylinder(it->params.cyl.radius, it->params.cyl.depth, it->params.cyl.isSteering, it->params.cyl.isRolling, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2], it->rotation);
			addShape(cyl);
		}
		
	}

}

myVehicle::myVehicle(VehicleModel remote)
{
	myVehicleModel();
	for (std::vector<ShapeInit>::iterator it = remote.shapes.begin(); it != remote.shapes.end(); ++it) 
	{
		if (it->type == RECTANGULAR_PRISM) 
		{
			rectangular* rec = NULL;
			rec = new rectangular(it->params.rect.xlen, it->params.rect.ylen, it->params.rect.zlen, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2]);
			addShape(rec);
		}

		else if (it->type == TRIANGULAR_PRISM)
		{
			triangular * tri = NULL;
			tri = new triangular(it->params.tri.alen, it->params.tri.blen, it->params.tri.depth, it->params.tri.angle, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2]);
			addShape(tri);
		}

		else if (it->type == TRAPEZOIDAL_PRISM)
		{
			trapezoidal * tra = NULL;
			tra = new trapezoidal(it->params.trap.alen, it->params.trap.blen, it->params.trap.height, it->params.trap.depth, it->params.trap.aoff, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2], it->rotation);
			addShape(tra);
		}

		else if (it->type == CYLINDER) 
		{
			cylinder * cyl = NULL;
			cyl = new cylinder(it->params.cyl.radius, it->params.cyl.depth, it->params.cyl.isSteering, it->params.cyl.isRolling, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2], it->rotation);
			addShape(cyl);
		}
	
	} 
}


void myVehicle::draw()
{
	cylinder* ptr = NULL;
	for (std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
		glPushMatrix();
		positionInGL();

		ptr = dynamic_cast <cylinder*>(*it);
		if (ptr != NULL)
		{
			ptr->checkRolling(speed);
			ptr->setRolling(speed);
			if (ptr->getSteering())
			{
				ptr->setRotate(steering);
			}
		}

		(*it)->draw();
		glPopMatrix();

	}
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