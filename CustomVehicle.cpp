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
	int x = 5;
	int y = 3;
	int z = 6;

	glPushMatrix();
	positionInGL();
	RectangularPrism Rectangle(x, y, z, 1, 0, 0);
	Rectangle.draw();

	glPushMatrix();
	glTranslatef(x, -y, -3);
	TriangularPrism Triangle(8, 10, 6, 90, 0, 1, 0);
	Triangle.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(3+x), 0.0, 0.0);
	Cylinder Cylinder(3, 12, 0, 0, 1);
	Cylinder.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, (3+y), 0.0);
	TrapezoidalPrism Trapezoid(6.0, 3.0, 6.0, 3.0, 1, 1, 1);
	Trapezoid.draw();
	glPopMatrix();

	glPopMatrix();

}
