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



#include "TrapezoidalPrism.h"

TrapezoidalPrism::TrapezoidalPrism()
{
	XLength = 2;
	YLength = 1;
	ZLength = 1;
	Offset = 1;
}

TrapezoidalPrism::TrapezoidalPrism(double XLength, double YLength, double ZLength, double Offset)
{
	this->XLength = XLength;
	this->YLength = YLength;
	this->ZLength = ZLength;
	this->Offset = Offset;
}

double TrapezoidalPrism::getXLength()
{
	return XLength;
}

double TrapezoidalPrism::getYLength()
{
	return YLength;
}

double TrapezoidalPrism::getZLength()
{
	return ZLength;
}

double TrapezoidalPrism::getOffset()
{
	return Offset;
}

void TrapezoidalPrism::setXLength(double XLength)
{
	this->XLength = XLength;
}

void TrapezoidalPrism::setYLength(double YLength)
{
	this->YLength = YLength;
}

void TrapezoidalPrism::setZLength(double ZLength)
{
	this->ZLength = ZLength;
}

void TrapezoidalPrism::setOffset(double Offset)
{
	this->Offset = Offset;
}

void TrapezoidalPrism::draw()
{
	glPushMatrix();
	//glLoadIdentity();
	//glTranslatef(1.5f, 0.0f, -6.0f);
	//glRotatef(rotation, 1.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);

	// Front face of prism
	glVertex3f(x - XLength, y - YLength, z - ZLength);
	glVertex3f(x + XLength, y - YLength, z - ZLength);
	glVertex3f(x + XLength - Offset, y + YLength, z - ZLength);
	glVertex3f(x - XLength + Offset, y + YLength, z - ZLength);

	// Back face of prism
	glVertex3f(x - XLength, y - YLength, z + ZLength);
	glVertex3f(x + XLength, y - YLength, z + ZLength);
	glVertex3f(x + XLength - Offset, y + YLength, z + ZLength);
	glVertex3f(x - XLength + Offset, y + YLength, z + ZLength);

	// Right face of prism
	glVertex3f(x + XLength, y - YLength, z - ZLength);
	glVertex3f(x + XLength, y - YLength, z + ZLength);
	glVertex3f(x + XLength - Offset, y + YLength, z + ZLength);
	glVertex3f(x + XLength - Offset, y + YLength, z - ZLength);

	// Left face of prism
	glVertex3f(x - XLength, y - YLength, z - ZLength);
	glVertex3f(x - XLength, y - YLength, z + ZLength);
	glVertex3f(x - XLength + Offset, y + YLength, z + ZLength);
	glVertex3f(x - XLength + Offset, y + YLength, z - ZLength);


	// Bottom face of prism
	glVertex3f(x - XLength, y - YLength, z - ZLength);
	glVertex3f(x + XLength, y - YLength, z - ZLength);
	glVertex3f(x + XLength, y - YLength, z + ZLength);
	glVertex3f(x - XLength, y - YLength, z + ZLength);

	// Top face of prism
	glVertex3f(x - XLength + Offset, y + YLength, z - ZLength);
	glVertex3f(x + XLength - Offset, y + YLength, z - ZLength);
	glVertex3f(x + XLength - Offset, y + YLength, z + ZLength);
	glVertex3f(x - XLength + Offset, y + YLength, z + ZLength);

	glEnd();
	//glFlush();
	glPopMatrix();

}
