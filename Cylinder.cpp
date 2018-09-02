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
#include "Cylinder.h"

Cylinder::Cylinder()
{
	this->Radius = 1;
	this->Length = 5;
}

Cylinder::Cylinder(double Radius, double Length)
{
	this->Radius = Radius;
	this->Length = Length;
}

double Cylinder::getRadius()
{
	return Radius;
}

double Cylinder::getLength()
{
	return Length;
}

void Cylinder::setRadius(double Radius)
{
	this->Radius = Radius;
}

void Cylinder::setLength(double Length)
{
	this->Length = Length;
}

void Cylinder::draw()
{
	glPushMatrix();
	//glLoadIdentity();
	//glTranslatef(1.5f, 0.0f, -6.0f);
	//glRotatef(rotation, 1.0, 0.0, 0.0);

	GLUquadric* cylinder = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluCylinder(cylinder, Radius, Radius, Length, 32, 1);
	gluDisk(cylinder, 0, Radius, 32, 32);
	glTranslatef(0, 0, Length);
	gluDisk(cylinder, 0, Radius, 32, 32);


	//glFlush();
	glPopMatrix();
}

