#pragma once

#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Vehicle.hpp"

class CustomVehicle : public Vehicle {
public:
	CustomVehicle();
	//CustomVehicle(VehicleModel model);
	float distance;


	void draw();

};