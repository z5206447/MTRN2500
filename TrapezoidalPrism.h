#pragma once

#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Shape.hpp"

class TrapezoidalPrism : public Shape {
private:
	double XLengthBottom;
	double XLengthTop;
	double YLength;
	double ZLength;
	double Offset;
	double r;
	double g;
	double b;

public:
	TrapezoidalPrism();
	TrapezoidalPrism(double XLengthBottom, double XLengthTop, double YLength, double ZLength, double Offset, double r, double g, double b);

	double getXLengthBottom();
	double getXLengthTop();
	double getYLength();
	double getZLength();
	double getOffset();

	void setXLengthBottom(double XLength);
	void setXLengthTop(double XLengthTop);
	void setYLength(double YLength);
	void setZLength(double ZLength);
	void setOffset(double Offset);

	void draw();

};