#pragma once

#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Shape.hpp"

class TriangularPrism : public Shape {
private:
	double ALength;
	double BLength;
	double Depth;
	double Angle;
	double r;
	double g;
	double b;

public:
	TriangularPrism();
	TriangularPrism(double ALength, double BLength, double Depth, double Angle, double r, double g, double b);

	double getALength();
	double getBLength();
	double getDepth();
	double getAngle();

	void setALength(double ALength);
	void setBLength(double BLength);
	void setDepth(double Depth);
	void setAngle(double ZLength);

	void draw();

};