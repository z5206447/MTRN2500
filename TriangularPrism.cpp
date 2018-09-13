#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <sys/time.h>
#elif defined(WIN32)
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <sys/time.h>
#endif

#include <cmath>

#include "TriangularPrism.h"

#define PI 3.14159265

TriangularPrism::TriangularPrism()
{
	ALength = 1.0;
	BLength = 1.0;
	Depth = 1.0;
	Angle = 90;
}

TriangularPrism::TriangularPrism(double ALength, double BLength, double Depth, double Angle, double r, double g, double b)
{
	this->ALength = ALength;
	this->BLength = BLength;
	this->Depth = Depth;
	this->Angle = Angle;
	this->r = r;
	this->g = g;
	this->b = b;
}

double TriangularPrism::getALength()
{
	return ALength;
}

double TriangularPrism::getBLength()
{
	return BLength;
}

double TriangularPrism::getDepth()
{
	return Depth;
}

double TriangularPrism::getAngle()
{
	return Angle;
}

void TriangularPrism::setALength(double ALength)
{
	this->ALength = ALength;
}

void TriangularPrism::setBLength(double BLength)
{
	this->BLength = BLength;
}

void TriangularPrism::setDepth(double Depth)
{
	this->Depth = Depth;
}

void TriangularPrism::setAngle(double Angle)
{
	this->Angle = Angle;
}

void TriangularPrism::draw()
{
	glPushMatrix();
	//glLoadIdentity();
	//glTranslatef(1.5f, 0.0f, -6.0f);
	//glRotatef(rotation, 1.0, 0.0, 0.0);
	glColor3f(red, green, blue);

	glTranslatef(x, y, z);
	glTranslatef(ALength/2, 0, Depth/2);
	glRotatef(180, 0, 1, 0);

	glBegin(GL_TRIANGLES);

	// Front face of prism
	glVertex3f(0, 0, 0);
	glVertex3f(+ALength, 0, 0);
	glVertex3f(+BLength * cos(Angle * PI / 180.0), +BLength * sin(Angle * PI / 180.0), 0);

	// Back face of prism
	glVertex3f(0, 0, 0 + Depth);
	glVertex3f(+ALength, 0, +Depth);
	glVertex3f(+BLength * cos(Angle * PI / 180.0), +BLength * sin(Angle * PI / 180.0), +Depth);

	glEnd();

	glBegin(GL_QUADS);

	//glColor3f(1.0, 0.0, 0.0);

	// Bottom face of prism
	glVertex3f(0, 0, 0);
	glVertex3f(+ALength, 0, 0);
	glVertex3f(+ALength, 0, +Depth);
	glVertex3f(0, 0, +Depth);

	//glColor3f(0.0, 1.0, 0.0);
	// Left face of Vertex
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, +Depth / 2);
	glVertex3f(+BLength * cos(Angle * PI / 180.0), +BLength * sin(Angle * PI / 180.0), +Depth);
	glVertex3f(+BLength * cos(Angle * PI / 180.0), +BLength * sin(Angle * PI / 180.0), 0);


	//glColor3f(1.0, 1.0, 1.0);
	// Right face of Vertex
	glVertex3f(+ALength, 0, 0);
	glVertex3f(+ALength, 0, +Depth);
	glVertex3f(+BLength * cos(Angle * PI / 180.0), +BLength * sin(Angle * PI / 180.0), +Depth);
	glVertex3f(+BLength * cos(Angle * PI / 180.0), +BLength * sin(Angle * PI / 180.0), 0);


	glEnd();
	//glFlush();
	glPopMatrix();

}


