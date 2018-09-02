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


#include "CustomVehicle.h"
#include "RectangularPrism.h"
#include "TriangularPrism.h"
#include "TrapezoidalPrism.h"
#include "Cylinder.h"

CustomVehicle::CustomVehicle()
{
}

void CustomVehicle::draw()
{	
	glPushMatrix();
	positionInGL();
	RectangularPrism Rectangle(3, 3, 3);
	Rectangle.draw();

	glPushMatrix();
	glTranslatef(3, -3.0, -3);
	TriangularPrism Triangle(6, 8, 6, 90);
	Triangle.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0, 0.0, -2);
	Cylinder Cylinder(2, 4);
	Cylinder.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 6, 0.0);
	TrapezoidalPrism Trapezoid(3.0, 3.0, 3.0, 1.0);
	Trapezoid.draw();
	glPopMatrix();

	glPopMatrix();

}
