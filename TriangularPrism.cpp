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

	glBegin(GL_TRIANGLES);

	// Front face of prism
	glVertex3f(x, y, z);
	glVertex3f(x + ALength, y, z);
	glVertex3f(x + BLength * cos(Angle * PI/180.0), y + BLength * sin(Angle * PI / 180.0), z);

	// Back face of prism
	glVertex3f(x, y, z + Depth);
	glVertex3f(x + ALength, y, z + Depth);
	glVertex3f(x + BLength * cos(Angle * PI / 180.0), y + BLength * sin(Angle * PI / 180.0), z + Depth);

	glEnd();

	glBegin(GL_QUADS);

	//glColor3f(1.0, 0.0, 0.0);

	// Bottom face of prism
	glVertex3f(x, y, z);
	glVertex3f(x + ALength, y, z);
	glVertex3f(x + ALength, y, z + Depth);
	glVertex3f(x, y, z + Depth);

	//glColor3f(0.0, 1.0, 0.0);
	// Left face of Vertex
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + Depth);
	glVertex3f(x + BLength * cos(Angle * PI / 180.0), y + BLength * sin(Angle * PI / 180.0), z + Depth);
	glVertex3f(x + BLength * cos(Angle * PI / 180.0), y + BLength * sin(Angle * PI / 180.0), z);


	//glColor3f(1.0, 1.0, 1.0);
	// Right face of Vertex
	glVertex3f(x + ALength, y, z);
	glVertex3f(x + ALength, y, z + Depth);
	glVertex3f(x + BLength * cos(Angle * PI / 180.0), y + BLength * sin(Angle * PI / 180.0), z + Depth);
	glVertex3f(x + BLength * cos(Angle * PI / 180.0), y + BLength * sin(Angle * PI / 180.0), z);


	glEnd();
	//glFlush();
	glPopMatrix();

}


