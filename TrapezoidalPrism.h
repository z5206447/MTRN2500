#pragma once

#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Shape.hpp"

class TrapezoidalPrism : public Shape {
private:
	double XLength;
	double YLength;
	double ZLength;
	double Offset;

public:
	TrapezoidalPrism();
	TrapezoidalPrism(double XLength, double YLength, double ZLength, double Offset);

	double getXLength();
	double getYLength();
	double getZLength();
	double getOffset();

	void setXLength(double XLength);
	void setYLength(double YLength);
	void setZLength(double ZLength);
	void setOffset(double Offset);

	void draw();

};