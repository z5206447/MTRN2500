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



#include "RectangularPrism.h"

RectangularPrism::RectangularPrism()
{
	XLength = 1.0;
	YLength = 1.0;
	ZLength = 1.0;
	this->setColor(1.0, 1.0, 1.0);
	/*this->r = 1.0;
	this->g = 1.0;
	this->b = 1.0;*/
}

/*RectangularPrism::RectangularPrism(double XLength, double YLength, double ZLength, double r, double g, double b)
{
	this->XLength = XLength;
	this->YLength = YLength;
	this->ZLength = ZLength;
	this->r = r;
	this->g = g;
	this->b = b;
}*/

double RectangularPrism::getXLength()
{
	return XLength;
}

double RectangularPrism::getYLength()
{
	return YLength;
}

double RectangularPrism::getZLength()
{
	return ZLength;
}

void RectangularPrism::setXLength(double XLength)
{
	this->XLength = XLength;
}

void RectangularPrism::setYLength(double YLength)
{
	this->YLength = YLength;
}

void RectangularPrism::setZLength(double ZLength)
{
	this->ZLength = ZLength;
}

void RectangularPrism::draw()
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

		// Bottom face of prism
		glVertex3f(-XLength / 2, -YLength / 2, -ZLength / 2);
		glVertex3f(+XLength / 2, -YLength / 2, -ZLength / 2);
		glVertex3f(+XLength / 2, +YLength / 2, -ZLength / 2);
		glVertex3f(-XLength / 2, +YLength / 2, -ZLength / 2);

		// Top face of prism
		glVertex3f(-XLength / 2, -YLength / 2, +ZLength / 2);
		glVertex3f(+XLength / 2, -YLength / 2, +ZLength / 2);
		glVertex3f(+XLength / 2, +YLength / 2, +ZLength / 2);
		glVertex3f(-XLength / 2, +YLength / 2, +ZLength / 2);

		// Front face of prism
		//glColor3f(0.0, 1.0, 0.0);
		glVertex3f(+XLength / 2, -YLength / 2, -ZLength / 2);
		glVertex3f(+XLength / 2, -YLength / 2, +ZLength / 2);
		glVertex3f(+XLength / 2, +YLength / 2, +ZLength / 2);
		glVertex3f(+XLength / 2, +YLength / 2, -ZLength / 2);

		// Back face of prism
		glVertex3f(-XLength / 2, -YLength / 2, -ZLength / 2);
		glVertex3f(-XLength / 2, -YLength / 2, +ZLength / 2);
		glVertex3f(-XLength / 2, +YLength / 2, +ZLength / 2);
		glVertex3f(-XLength / 2, +YLength / 2, -ZLength / 2);


		// Left face of prism
		//glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-XLength / 2, -YLength / 2, -ZLength / 2);
		glVertex3f(+XLength / 2, -YLength / 2, -ZLength / 2);
		glVertex3f(+XLength / 2, -YLength / 2, +ZLength / 2);
		glVertex3f(-XLength / 2, -YLength / 2, +ZLength / 2);

		// Right face of prism
		glVertex3f(-XLength / 2, +YLength / 2, -ZLength / 2);
		glVertex3f(+XLength / 2, +YLength / 2, -ZLength / 2);
		glVertex3f(+XLength / 2, +YLength / 2, +ZLength / 2);
		glVertex3f(-XLength / 2, +YLength / 2, +ZLength / 2);

	glEnd();
	//glFlush();
	glPopMatrix();

}


