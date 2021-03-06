#pragma once

#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Shape.hpp"

class RectangularPrism : public Shape {
private:
	double XLength;
	double YLength;
	double ZLength;
	double r;
	double g;
	double b;

public:
	RectangularPrism();
	RectangularPrism(double XLength, double YLength, double ZLength, double r, double g, double b);

	double getXLength();
	double getYLength();
	double getZLength();

	void setXLength(double XLength);
	void setYLength(double YLength);
	void setZLength(double ZLength);

	void draw();

};