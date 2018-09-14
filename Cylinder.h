#pragma once

#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Shape.hpp"

class Cylinder : public Shape {
private:
	double Radius;
	double Length;
	bool isRolling;
	bool isSteering;

public:
	Cylinder();
	//Cylinder(double Radius, double Length);

	double getRadius();
	double getLength();
	bool getRolling();
	bool getSteering();

	void setRadius(double Radius);
	void setLength(double Length);
	void setRolling(bool Rolling);
	void setSteering(bool Steering);

	void draw();

};