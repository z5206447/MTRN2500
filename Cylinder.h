#pragma once

#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Shape.hpp"

class Cylinder : public Shape {
private:
	double Radius;
	double Length;
	double r;
	double g;
	double b;
	bool Steering;
	bool Rolling;

public:
	Cylinder();
	Cylinder(double Radius, double Length, double r, double g, double b);

	double getRadius();
	double getLength();

	bool getSteering();
	bool getRolling();


	void setRadius(double Radius);
	void setLength(double Length);


	void setSteering(bool Steering);
	void SetRolling(bool Rolling);
	void draw();

};