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

Cylinder::Cylinder(double Radius, double Length, double r, double g, double b)
{
	this->Radius = Radius;
	this->Length = Length;
	this->r = r;
	this->g = g;
	this->b = b;
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
	glColor3f(red, green, blue);
	glTranslatef(x, y, z);
	glTranslatef(0, 0, -Length / 2);
	gluCylinder(cylinder, Radius, Radius, Length, 32, 1);


	gluDisk(cylinder, 0, Radius, 32, 32);
	glBegin(GL_LINES);

	glColor3f(0, 1, 1);
	glVertex3f(Radius, 0, Length/2);
	glVertex3f(-Radius, 0, Length / 2);
	glVertex3f(0, Radius, Length / 2);
	glVertex3f(0, -Radius, Length / 2);

	glVertex3f(Radius, 0, -Length / 2);
	glVertex3f(-Radius, 0, -Length / 2);
	glVertex3f(0, Radius, -Length / 2);
	glVertex3f(0, -Radius, -Length / 2);
	glEnd();

	glColor3f(r, g, b);
	glTranslatef(0, 0, Length / 2);
	gluDisk(cylinder, 0, Radius, 32, 32);

	//glFlush();
	glPopMatrix();
}

