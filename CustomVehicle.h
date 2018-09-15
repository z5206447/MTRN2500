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
	
	std::vector<Shape *>::iterator getBegin();
	std::vector<Shape *>::iterator getEnd();
	float distance;


	void draw();

};