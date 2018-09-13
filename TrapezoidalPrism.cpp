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
	XLengthBottom = 2;
	XLengthTop = 1;
	YLength = 1;
	ZLength = 1;
	Offset = 1;
}

TrapezoidalPrism::TrapezoidalPrism(double XLengthBottom, double XLengthTop, double YLength, double ZLength, double Offset, double r, double g, double b)
{
	this->XLengthBottom = XLengthBottom;
	this->XLengthTop = XLengthTop;
	this->YLength = YLength;
	this->ZLength = ZLength;
	this->Offset = Offset;
	this->r = r;
	this->g = g;
	this->b = b;
}

double TrapezoidalPrism::getXLengthBottom()
{
	return XLengthBottom;
}

double TrapezoidalPrism::getXLengthTop()
{
	return XLengthTop;
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



void TrapezoidalPrism::setXLengthBottom(double XLength)
{
	this->XLengthBottom = XLength;
}

void TrapezoidalPrism::setXLengthTop(double XLengthTop)
{
	this->XLengthTop = XLengthTop;
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

	glColor3f(red, green, blue);
	glTranslatef(x, y + YLength / 2, z);
	glRotatef(180, 0, 1, 0);
	glRotatef(rotation, 1.0, 0.0, 0.0);

	glBegin(GL_QUADS);

	// Front face of prism
	glVertex3f(-XLengthBottom /2, -YLength / 2, -ZLength / 2);
	glVertex3f(+XLengthBottom / 2, -YLength / 2, -ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset, +YLength / 2, -ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset - XLengthTop, +YLength / 2, z - ZLength / 2);

	// Back face of prism
	glVertex3f(-XLengthBottom / 2, -YLength / 2, +ZLength / 2);
	glVertex3f(+XLengthBottom / 2, -YLength / 2, +ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset, +YLength / 2, +ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset - XLengthTop, +YLength / 2, +ZLength / 2);

	// Left face of prism
	glVertex3f(+XLengthBottom / 2, -YLength / 2, -ZLength / 2);
	glVertex3f(+XLengthBottom / 2, -YLength / 2, +ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset, +YLength / 2, +ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset, +YLength / 2, -ZLength / 2);

	// Right face of prism
	glVertex3f(-XLengthBottom / 2, -YLength / 2, -ZLength / 2);
	glVertex3f(-XLengthBottom / 2, -YLength / 2, +ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset - XLengthTop, +YLength / 2, +ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset - XLengthTop, +YLength / 2, -ZLength / 2);


	// Bottom face of prism
	glVertex3f(-XLengthBottom / 2, -YLength / 2, -ZLength / 2);
	glVertex3f(+XLengthBottom / 2, -YLength / 2, -ZLength / 2);
	glVertex3f(+XLengthBottom / 2, -YLength / 2, +ZLength / 2);
	glVertex3f(-XLengthBottom / 2, -YLength / 2, +ZLength / 2);

	// Top face of prism
	glVertex3f(+XLengthBottom / 2 - Offset - XLengthTop, +YLength / 2, -ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset, +YLength / 2, -ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset, +YLength / 2, +ZLength / 2);
	glVertex3f(+XLengthBottom / 2 - Offset - XLengthTop, +YLength / 2, +ZLength / 2);

	glEnd();
	//glFlush();
	glPopMatrix();

}
