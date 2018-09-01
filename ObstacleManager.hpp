
#ifndef MTRN3500_OBSTACLEMANAGER_H
#define MTRN3500_OBSTACLEMANAGER_H

#include <list>
#include "Obstacle.hpp"

class ObstacleManager {

private:
	static ObstacleManager * instance;
	std::list<Obstacle> obstacles;

protected:
	ObstacleManager();
	~ObstacleManager();

public:
	static ObstacleManager * get();

	void addObstacle(Obstacle o);
	void drawAll();
	void removeAll();

	bool isColliding(double x, double y, double radius);

	std::list<Obstacle> getObstacles(double x, double y, double radius);

};

#endif // for MTRN3500_OBSTACLEMANAGER_H
