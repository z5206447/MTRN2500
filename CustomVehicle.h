#pragma once

#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Vehicle.hpp"
#include "Messages.hpp"

class CustomVehicle : public Vehicle {
public:
	CustomVehicle();
	CustomVehicle(VehicleModel vm);
	float distance;


	void draw();

};