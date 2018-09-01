
#include "ObstacleManager.hpp"
#include <math.h>
#include <iostream>
using namespace std;

ObstacleManager * ObstacleManager::instance = NULL;

ObstacleManager::ObstacleManager() {



};

ObstacleManager::~ObstacleManager() {

};

ObstacleManager * ObstacleManager::get() {
	if (instance == NULL) {
		instance = new ObstacleManager();
	}
	return instance;
};

void ObstacleManager::addObstacle(Obstacle o) {

	// prevent obstacles from being double added to the list
	for (std::list<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++) {
		Obstacle oo = (*it);
		if (o.equals(oo)) return;
	}

	obstacles.push_back(o);
};

void ObstacleManager::drawAll() {
	for (std::list<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++) {
			it->draw();
	}
};

void ObstacleManager::removeAll() {
	obstacles.clear();
};

std::list<Obstacle> ObstacleManager::getObstacles(double x, double y, double r) {

	std::list<Obstacle> ret;
	for (std::list<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++) {
		double dx = (it->getX() - x);
		double dy = (it->getZ() - y);
		double dist = sqrt((dx*dx) + (dy*dy)) - (it->getRadius());
		if(dist < r) 
			ret.push_back(*it);
	}

	return ret;
}


bool ObstacleManager::isColliding(double x, double y, double r) {

	return !getObstacles(x, y, r).empty();
}

