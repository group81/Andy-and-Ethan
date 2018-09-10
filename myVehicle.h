
#include "Vehicle.hpp"
#include <iostream>

class myVehicle : public Vehicle
{
public:
	myVehicle();
	myVehicle(VehicleModel remote);
	void draw();
	void myVehicleModel();
	VehicleModel setLocal();
private:
	VehicleModel local; //Structure with "VehicleModel" type of local data
	VehicleModel remote;  //Structure with "VehicleModel" type of remote data
};

